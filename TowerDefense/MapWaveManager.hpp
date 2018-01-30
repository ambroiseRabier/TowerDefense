#pragma once
#ifndef MAP_WAVE_MANAGER_HPP
#define MAP_WAVE_MANAGER_HPP
#include "Minion.hpp"
#include "MapParams.hpp"

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
			static unsigned int wave_index;
			static unsigned int minion_wave_index;
			static unsigned minion_time_out_id;
			static unsigned minion_wave_time_out_id;
			static void init();

			/**
			 * \brief Use this to load all minions in pool. or just to save parameters.
			 * \param map_params 
			 */
			static void load_minions(const Game::MapParams* new_map_params);

			/**
			 * \brief When the game begin !
			 */
			static void start();
			static void next_wave();
			static void next_minon_wave();
			static void spawn(const Game::MinionId& minion_id);
			static const float get_delay_before_next_wave();
			static const float get_delay_before_next_minion_wave();
			static bool next_wave_valid();
			static bool next_minion_wave_valid();
			static bool is_end_of_wave();

			/**
			 * \brief Call this if destroyed early, before map destroy.
			 * It avoid that you are destroyed two time.
			 */
			static void destroy_me(GameEngine::BaseGameObject& to_delete);
		private:
			static void destroy_current_level();
			static const Game::MapParams* map_params;
		};
	}
}
#endif

