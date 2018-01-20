#include "stdafx.h"
#include "MapManager.hpp"
#include "GameEngine/Debug.hpp"

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
			TowerDefense::GameEngine::Debug::assert_m(level_loaded_flag, "MapManager: No level to destroy was found.");
			//todo
		}

		void MapManager::load_level_internal(const unsigned int& level_number)
		{
		}
	}
}
