#pragma once
#ifndef MAP_WAVE_MANAGER_HPP
#define MAP_WAVE_MANAGER_HPP
#include "Minion.hpp"
#include <memory>
#include "Health.hpp"
#include <memory>

// s'occupe du spawn des wave du minion
// s'assure que get_level_loaded_flag == true
// contient une ref vers les waves a spawn 
// est enti�rement control� par map manager?
// ou plutot control� par gamemanager pour �vtyenullement laisser un temps pour poser les tours
// avant de spawn les ennemis.
// dans tout les cas ce manager s'appuie beaucoup sur MapManager
// et peut-�tre renoimm� MapManager MapTileManager.
namespace TowerDefense
{
	namespace Managers
	{
		class MapWaveManager
		{
		public:
			static std::unique_ptr<Game::Minion> temp_minion;
			static std::unique_ptr<Game::Health> temp_life_bar;
			static void init();
			static void destroy();
			static void start_wave_spawn();
		};
	}
}
#endif

