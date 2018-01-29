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
		std::unique_ptr<Minion> MapWaveManager::temp_minion;

		void MapWaveManager::init()
		{
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&GlobalShared::destroy);
		}

		void MapWaveManager::destroy()
		{
			if (temp_minion.get()) temp_minion.reset(nullptr);
		}

		void MapWaveManager::start_wave_spawn()
		{
			temp_minion = std::unique_ptr<Minion>(Minion::create_peon(MapManager::get_spawn().map_pos));
			temp_minion->get_transformable().setPosition(
				MapManager::get_spawn().get_transformable().getPosition()
			);
			temp_minion->auto_start();
		}

		void MapWaveManager::destroy_current_level()
		{
			temp_minion.reset(nullptr);
		}
	}
}
