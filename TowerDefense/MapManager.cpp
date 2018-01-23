#include "stdafx.h"
#include "MapManager.hpp"
#include "GameEngine/Debug.hpp"
#include "MapParams.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include "Managers/GameManager.hpp"

namespace TowerDefense
{
	namespace Managers
	{
		std::shared_ptr<Castle> MapManager::castle;
		std::shared_ptr<Spawn> MapManager::spawn;
		bool MapManager::level_loaded_flag;
		const MapParams* MapManager::map_params;
		std::map<int, std::map<int, std::shared_ptr<Tile>>> MapManager::all_tiles;

		Castle& MapManager::get_castle()
		{
			return *castle.get();
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
			if (castle.get())
				castle.reset();
			if (spawn.get())
				spawn.reset();
			if (!all_tiles.empty())
			{
				for (auto all_tile : all_tiles)
				{
					for (auto tile_id : all_tile.second)
					{
						tile_id.second.reset();
					}
					all_tile.second.clear();
				}
				all_tiles.clear();
			}

			level_loaded_flag = false;
		}

		const bool MapManager::get_level_loaded_flag()
		{
			return level_loaded_flag;
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
			create_tiles(*map_params);
		}

		void MapManager::create_tiles(const MapParams l_map_params)
		{
			const int length = l_map_params.map_background_tile_array.size();
			for(int x = 0; x < length ; x++) {
				std::vector<TileId> row =l_map_params.map_background_tile_array.at(x);
				for(int y = 0; y < row.size() ; y++) {
					const TileId tile_id = row.at(y);
					/*if (all_tiles.empty())
					{
						all_tiles = {};
					}
					if (all_tiles[x].empty())
					{
						all_tiles[x] = {};
					}*/
					auto cc = spawn_tile(tile_id);
					cc->auto_start();
					cc->get_transformable().setPosition(x*100, y*100);/*
					all_tiles[x][y] = spawn_tile(tile_id);
					all_tiles[x][y]->x = x;
					all_tiles[x][y]->y = y;
					all_tiles[x][y]->get_transformable().setPosition(x*100, y*100);*/
					//all_tiles[x][y]->auto_start();
				}
			}
		}

		std::shared_ptr<Tile> MapManager::spawn_tile(const TileId tile_id)
		{
			switch (tile_id)
			{
			case Castle_Other:
				castle = std::make_shared<Castle>();
				return static_cast<std::shared_ptr<Tile>>(castle);
			case Spawn_Other:
				spawn = std::make_shared<Spawn>();
				return static_cast<std::shared_ptr<Tile>>(spawn);
			case Grass_Build:
				return std::make_shared<Tile>(GlobalShared::grass_build_texture, Grass_Build);
			case Road_Walk:
				return std::make_shared<Tile>(GlobalShared::road_walk_texture, Road_Walk);
			default:
				Debug::warn("MapManager: No tile corresponding to TileId found. Add one.");
				return std::make_shared<Tile>(GlobalShared::missing_texture_tile_texture, Missing_texture);
			}
		}
	}
}
