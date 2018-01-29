#include "stdafx.h"
#include "MapWaveManager.hpp"
#include "Health.hpp"
#include "Minion.hpp"
#include "GlobalShared.hpp"
#include "MapManager.hpp"

using namespace TowerDefense::Game;
namespace TowerDefense
{
	namespace Managers
	{
		Minion* MapWaveManager::temp_minion;

		void MapWaveManager::init()
		{
			MapManager::on_destroy_level += Sharp::EventHandler::Bind(&MapWaveManager::destroy_current_level);
		}

		void MapWaveManager::start_wave_spawn()
		{
			temp_minion = Minion::create_peon(MapManager::get_spawn().map_pos);
			temp_minion->get_transformable().setPosition(
				MapManager::get_spawn().get_transformable().getPosition()
			);
			temp_minion->auto_start();
			// minoin manage it's memory itself, todo: move getTransformable and auto_start. or not ? because event iterator :/
		}

		void MapWaveManager::destroy_current_level()
		{
			if (temp_minion != nullptr)
			{
				temp_minion->on_destroy_map();
				temp_minion = nullptr;
			}
		}
	}
}
