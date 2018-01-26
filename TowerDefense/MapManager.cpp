#include "stdafx.h"
#include "MapManager.hpp"
#include "GameEngine/Debug.hpp"
#include "MapParams.hpp"
#include "Player.hpp"
#include "Managers/GameManager.hpp"
#include "Align.hpp"
#include "LevelDesign.hpp"
#include "Assets.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace Managers
	{
		Castle* MapManager::castle;
		Spawn* MapManager::spawn;
		bool MapManager::level_loaded_flag;
		const MapParams* MapManager::map_params;
		//std::map<int, std::map<int, std::shared_ptr<Tile>*>> MapManager::all_tiles;
		std::map<unsigned int, std::map<unsigned int, Tile*>> MapManager::all_tiles_p;
		sf::Transformable MapManager::map_origin;

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
			// nothing :/
		}

		void MapManager::load_level(const unsigned int& level_number)
		{
			if (level_loaded_flag)
			{
				destroy_current_level();
			}
			load_level_internal(level_number);
			level_loaded_flag = true;
		}

		void MapManager::destroy_current_level()
		{
			Debug::assert_m(level_loaded_flag, "MapManager: No level to destroy was found.");
			/*if (castle.get())
				castle.reset();
			if (spawn.get())
				spawn.reset();*/
			if (castle)
			{
				castle = nullptr;
			}
			if (spawn)
			{
				spawn = nullptr;
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

			level_loaded_flag = false;
		}

		const bool MapManager::get_level_loaded_flag()
		{
			return level_loaded_flag;
		}

		const sf::Transformable& MapManager::get_map_origin()
		{
			return map_origin;
		}

		void MapManager::load_level_internal(const unsigned int& level_number)
		{
			Debug::assert_m(!level_loaded_flag, "A level is already loaded.");
			if (level_number != 0)
			{
				Debug::warn("Only one level supported for now.");
				return;
			}
			map_params = &Constants::LevelDesign::level0;
			GameManager::get_player().set_money(map_params->start_money);
			align_center(*map_params);
			create_tiles(*map_params);
		}

		void MapManager::align_center(const MapParams l_map_params)
		{
			auto game_object_hightest_z = *std::max_element(
			l_map_params.map_background_tile_array.begin(),
				l_map_params.map_background_tile_array.end(),
				compare_row_size_p
			);
			const sf::Vector2f map_size(
				// converting to float will make it lose precision, but it's okay there never will be so many tiles.
				static_cast<float>(l_map_params.map_background_tile_array.size()) * Constants::Assets::tile_size,
				static_cast<float>(game_object_hightest_z.size()) * Constants::Assets::tile_size
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
				std::vector<TileId> row =l_map_params.map_background_tile_array.at(y);
				const auto length2 = row.size();
				for(unsigned int x = 0; x < length2 ; x++) {
					const TileId tile_id = row.at(x);
					/*if (all_tiles.empty())
					{
						all_tiles = {};
					}
					if (all_tiles[x].empty())
					{
						all_tiles[x] = new std::map<int, std::shared_ptr<Tile>>();
						std::map<int, std::shared_ptr<Tile>>* cj = new std::map<int, std::shared_ptr<Tile>>();
						all_tiles[x] = {};
					}
					auto cc = spawn_tile(tile_id);
					cc->auto_start();
					cc->get_transformable().setPosition(x*100, y*100);*//*
					all_tiles[x][y] = spawn_tile(tile_id);
					all_tiles[x][y]->x = x;
					all_tiles[x][y]->y = y;
					all_tiles[x][y]->get_transformable().setPosition(x*100, y*100);*/
					//all_tiles[x][y]->auto_start();
					/*all_tiles[x][y] = spawn_tile(tile_id);
					all_tiles[x][y]->get_transformable().setPosition(x*100,y*100);
					all_tiles[x][y]->auto_start();*/
					all_tiles_p[x][y] = spawn_tile(tile_id, sf::Vector2u(x,y));
					all_tiles_p[x][y]->auto_start();
				}
			}
		}

		// like to make it work with shared ptr, huuum
		/*std::shared_ptr<Tile>* MapManager::spawn_tile(const TileId tile_id)
		{
			switch (tile_id)
			{
			case Castle_Other:
				castle = std::make_shared<Castle>();
				return static_cast<std::shared_ptr<Tile>*>(castle);
			case Spawn_Other:
				spawn = std::make_shared<Spawn>();
				return static_cast<std::shared_ptr<Tile>*>(spawn);
			case Grass_Build:
				return &std::make_shared<Tile>(GlobalShared::grass_build_texture, Grass_Build);
			case Road_Walk:
				return &std::make_shared<Tile>(GlobalShared::road_walk_texture, Road_Walk);
			default:
				Debug::warn("MapManager: No tile corresponding to TileId found. Add one.");
				return &std::make_shared<Tile>(GlobalShared::missing_texture_tile_texture, Missing_texture);
			}
		}*/

		
		Tile* MapManager::spawn_tile(const TileId tile_id, const sf::Vector2u& map_pos)
		{
			switch (tile_id)
			{
			case Castle_Other:
				castle = new Castle(map_pos);
				return static_cast<Tile*>(castle);
			case Spawn_Other:
				spawn = new Spawn(map_pos);
				return static_cast<Tile*>(spawn);
			case Grass_Build:
				return new Tile(GlobalShared::grass_build_texture, Grass_Build, map_pos);
			case Road_Walk:
				return new Tile(GlobalShared::road_walk_texture, Road_Walk, map_pos);
			default:
				Debug::warn("MapManager: No tile corresponding to TileId found. Add one.");
				return new Tile(GlobalShared::missing_texture_tile_texture, Missing_texture, map_pos);
			}
		}

		bool MapManager::compare_row_size_p(const std::vector<TileId> first, const std::vector<TileId> second)
		{
			return first.size() < second.size();
		}
	}
}
