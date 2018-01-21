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
		std::unique_ptr<Castle> MapManager::castle;
		bool MapManager::level_loaded_flag;

		Castle& MapManager::get_castle()
		{
			return *castle.get();
		}

		void MapManager::load_level(const unsigned int& level_number)
		{
			if (level_loaded_flag)
			{
				destroy_current_level();
				level_loaded_flag = false;
			}
			load_level_internal(level_number);
			level_loaded_flag = true;
		}

		void MapManager::destroy_current_level()
		{
			GameEngine::Debug::assert_m(level_loaded_flag, "MapManager: No level to destroy was found.");
			//todo
		}

		void MapManager::load_level_internal(const unsigned int& level_number)
		{
			if (level_number != 0)
			{
				Debug::warn("Only one level supported for now.");
				return;
			}
			const MapParams params = Constants::LevelDesign::level0;
			GameManager::get_player().set_money(params.start_money);
			for (const std::vector<std::vector<TileId>>::value_type column : params.map_background_tile_array)
			{
				for (const TileId tile : column)
				{
					spawn_tile(tile, index et ouais bro);
				}
			}
		}

		void MapManager::spawn_tile(TileId tile_id)
		{
			switch (tile_id)
			{
			case Castle_Other: 
				castle = std::make_unique<Castle>();
				break;
					
			}
		}
	}
}
