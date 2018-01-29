#pragma once
#ifndef MAP_WAVE_MANAGER_HPP
#define MAP_WAVE_MANAGER_HPP
#include "Minion.hpp"

// s'occupe du spawn des wave du minion
// s'assure que get_level_loaded_flag == true
// contient une ref vers les waves a spawn 
// est entièrement controlé par map manager?
// ou plutot controlé par gamemanager pour évtyenullement laisser un temps pour poser les tours
// avant de spawn les ennemis.
// dans tout les cas ce manager s'appuie beaucoup sur MapManager
// et peut-être renoimmé MapManager MapTileManager.
namespace TowerDefense
{
	namespace Managers
	{
		class MapWaveManager
		{
		public:

			static std::list<GameEngine::BaseGameObject*> instanciated_elements;
			static void init();
			static void start_wave_spawn();
			/**
			 * \brief Call this if destroyed early, before map destroy.
			 * It avoid that you are destroyed two time.
			 */
			static void destroy_me(GameEngine::BaseGameObject& to_delete);
		private:
			static void destroy_current_level();
		};
	}
}
#endif

