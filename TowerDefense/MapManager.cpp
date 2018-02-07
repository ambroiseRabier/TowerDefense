#include "stdafx.h"
#include "MapManager.hpp"
#include "GameEngine/Debug.hpp"
#include "MapParams.hpp"
#include "Player.hpp"
#include "Managers/GameManager.hpp"
#include "Align.hpp"
#include "Hud.hpp"
#include "Assets.hpp"
#include "MapWaveManager.hpp"
#include "AssetsConfig.hpp"
#include "TileAssets.hpp"
#include "GameDesign.hpp"
#include "GameEngine/DisplayManager.hpp"

namespace TowerDefense
{
	namespace Managers
	{
		std::unique_ptr<GameObject> MapManager::background;
		Castle* MapManager::castle;
		Spawn* MapManager::spawn;
		bool MapManager::level_loaded_flag;
		const MapParams* MapManager::map_params;
		//std::map<int, std::map<int, std::shared_ptr<Tile>*>> MapManager::all_tiles;
		std::map<unsigned int, std::map<unsigned int, Tile*>> MapManager::all_tiles_p;
		sf::Transformable MapManager::map_origin;
		Sharp::Event<void> MapManager::on_destroy_level;

		Castle& MapManager::get_castle()
		{
			Debug::assert_m(castle, "MapManager: castle being nullptr is unexpected.");
			return *castle;
		}

		Spawn& MapManager::get_spawn()
		{
			Debug::assert_m(spawn, "MapManager: spawn being nullptr is unexpected.");
			return *spawn;
		}

		void MapManager::init()
		{
			// nothing :/ maybe could load background here, but would need to destroy it on quit game !
		}

		void MapManager::load_level(const MapParams& new_map_params)
		{
			if (level_loaded_flag)
			{
				destroy_current_level();
			}
			load_level_internal(new_map_params);
			level_loaded_flag = true;
			background = std::make_unique<GameObject>(
				std::make_shared<sf::Sprite>(*GlobalShared::get_texture(Constants::Assets::level_background)),
				Constants::ZIndex::level_background
			);
			UI::Align::center(
				background->get_transformable(),
				sf::Vector2f(
					-static_cast<float>(GlobalShared::get_texture(Constants::Assets::level_background)->getSize().x)/2.f,
					-static_cast<float>(GlobalShared::get_texture(Constants::Assets::level_background)->getSize().y)/2.f
				)
			);
			DisplayManager::addChild(*background);
		}

		void MapManager::destroy_current_level()
		{
			Debug::assert_m(level_loaded_flag, "MapManager: No level to destroy was found.");
			on_destroy_level();
			/*if (castle.get())
				castle.reset();
			if (spawn.get())
				spawn.reset();*/
			assert(background);
			DisplayManager::remove_child(*background);
			background.reset(nullptr);
			if (castle)
			{
				castle = nullptr;
				// will be deleted, it is in all_tiles_p
			}
			if (spawn)
			{
				spawn = nullptr;
				// will be deleted, it is in all_tiles_p
			}
			if (!all_tiles_p.empty())
			{
				for (auto all_tile : all_tiles_p)
				{
					for (auto tile: all_tile.second)
					{
						delete tile.second;
						tile.second = nullptr;
					}
					all_tile.second.clear();
				}
				all_tiles_p.clear();
			}
			map_params = nullptr;
			level_loaded_flag = false;
		}

		bool MapManager::map_pos_exist(const sf::Vector2u map_pos)
		{
			return static_cast<bool>(all_tiles_p.count(map_pos.x)) 
				&& static_cast<bool>(all_tiles_p[map_pos.x].count(map_pos.y));
		}

		bool MapManager::map_pos_exist(const sf::Vector2i map_pos)
		{
			if (map_pos.x < 0 || map_pos.y < 0) return false;
			else return map_pos_exist(static_cast<sf::Vector2u>(map_pos));
		}

		bool MapManager::map_pos_walkable(const sf::Vector2u& map_pos)
		{
			// should use exist function on an constant array of walkable tileId, not kiss right now...
			const TileId destination = all_tiles_p[map_pos.x][map_pos.y]->get_tile_id();
			const bool found = std::find(
				Constants::GameDesign::walkable_tile.begin(), 
				Constants::GameDesign::walkable_tile.end(), 
				destination
			) != Constants::GameDesign::walkable_tile.end();

			return found;
		}

		bool MapManager::map_pos_walkable(const sf::Vector2i& map_pos)
		{
			if (map_pos.x < 0 || map_pos.y < 0) return false;
			else return map_pos_walkable(static_cast<sf::Vector2u>(map_pos));
		}

		bool MapManager::map_pos_buildable(const sf::Vector2u& map_pos)
		{
			const TileId destination = all_tiles_p[map_pos.x][map_pos.y]->get_tile_id();
			const bool found = std::find(
				Constants::GameDesign::buildable_tile.begin(), 
				Constants::GameDesign::buildable_tile.end(), 
				destination
			) != Constants::GameDesign::buildable_tile.end();

			return found;
		}

		bool MapManager::map_pos_buildable(const sf::Vector2i& map_pos)
		{
			if (map_pos.x < 0 || map_pos.y < 0) return false;
			else return map_pos_buildable(static_cast<sf::Vector2u>(map_pos));
		}

		sf::Vector2i MapManager::point_to_map_pos(const sf::Vector2i& mouse_position)
		{
			const sf::Vector2i local_pos = mouse_position - static_cast<sf::Vector2i>(map_origin.getPosition());
			const sf::Vector2i map_pos(
				/*std::max(0u, */(local_pos.x - (local_pos.x % Constants::AssetsConfig::tile_size_i)) / Constants::AssetsConfig::tile_size_i/*)*/,
				/*std::max(0u, */(local_pos.y - (local_pos.y % Constants::AssetsConfig::tile_size_i)) / Constants::AssetsConfig::tile_size_i/*)*/
			);
			const sf::Vector2i offset(
				local_pos.x < 0 ? -1 : 0,
				local_pos.y < 0 ? -1 : 0
			);
			return map_pos + offset;
		}

		const bool MapManager::get_level_loaded_flag()
		{
			return level_loaded_flag;
		}

		const sf::Transformable& MapManager::get_map_origin()
		{
			return map_origin;
		}

		void MapManager::load_level_internal(const MapParams& new_map_params)
		{
			Debug::assert_m(!level_loaded_flag, "A level is already loaded.");
			map_params = &new_map_params;
			UI::Hud::set_level_text(map_params->name);
			align_center_map(*map_params);
			create_tiles(*map_params);
			MapWaveManager::load_minions(map_params);
			Player::set_initial_money(map_params->start_money);
			Player::set_castle(castle);
		}

		void MapManager::align_center_map(const MapParams l_map_params)
		{
			auto game_object_hightest_z = *std::max_element(
			l_map_params.map_background_tile_array.begin(),
				l_map_params.map_background_tile_array.end(),
				compare_row_size_p
			);
			const sf::Vector2f map_size(
				// converting to float will make it lose precision, but it's okay there never will be so many tiles.
				static_cast<float>(l_map_params.map_background_tile_array.size()) * Constants::AssetsConfig::tile_size,
				static_cast<float>(game_object_hightest_z.size()) * Constants::AssetsConfig::tile_size
			);
			UI::Align::center(
				map_origin,
				sf::Vector2f(
					-map_size.x/2,
					-map_size.y/2
				)
			);
		}

		void MapManager::create_tiles(const MapParams l_map_params)
		{
			// should I really cache the length ?? (regarding performance)
			const auto length = l_map_params.map_background_tile_array.size();
			for(unsigned int y = 0; y < length ; y++) {
				std::vector<TileId> row = l_map_params.map_background_tile_array.at(y);
				const auto length2 = row.size();
				for(unsigned int x = 0; x < length2 ; x++) {
					const TileId tile_id = row.at(x);
					all_tiles_p[x][y] = spawn_tile(tile_id, sf::Vector2u(x,y));
					all_tiles_p[x][y]->auto_start();
				}
			}
		}
		
		Tile* MapManager::spawn_tile(const TileId tile_id, const sf::Vector2u& map_pos)
		{
			// todo: use switch
			if (tile_id == TileId::Castle_Other)
			{
				castle = new Castle(map_pos);
				return castle;
			} 
			else if (tile_id == TileId::Spawn_Other)
			{
				spawn = new Spawn(map_pos);
				return spawn;
			}
			else 
			{
				return new Tile(tile_id, map_pos);
			}
		}

		bool MapManager::compare_row_size_p(const std::vector<TileId> first, const std::vector<TileId> second)
		{
			return first.size() < second.size();
		}
	}
}
