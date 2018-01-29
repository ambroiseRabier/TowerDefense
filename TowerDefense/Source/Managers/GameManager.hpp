#pragma once
// to know : https://stackoverflow.com/questions/152555/h-or-hpp-for-your-class-definitions
#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include "Utils/Event.h"
#include "../../Player.hpp"

namespace TowerDefense
{
	namespace Managers
	{
		enum class GameState { Menu, Playing, Pause };
		/**
		 * \brief Manbage game states, also manage UI. (making an UIManager seem overkil)
		 */
		class GameManager
		{
		public: 
			static Sharp::Event<void> on_update;
			static void init(sf::RenderWindow* new_window_ref);
			static void start();
			static void update();
			static void start_level(const unsigned int& i);
			static void restart_level();
			static void pause();
			static void un_pause();
			static void return_menu();
			static void exit_game();
			static void up_game_speed();
			static GameState state;
			static const float& get_game_speed();
			static const float& get_fixed_delta_time();
			static const float& get_delta_time();
			/**
			 * \brief 
			 * \return scaled time since GameManager start in seconds.
			 */
			static const double& get_clock();
			/**
			 * \brief 
			 * \return fixed clock time since application start.
			 */
			static const sf::Clock& get_fixed_clock();
			static Game::Player& get_player();
		private:
			static void destroy();
			/**
			 * \brief 
			 * Speed the turret and minions.
			 */
			static unsigned int game_speed_index;
			static unsigned int level_index;
			static std::unique_ptr<Game::Player> player;
			static float fixed_delta_time;
			static float delta_time;
			static sf::Clock clock;
			/**
			 * \brief Not a Clock since I cannot set the clock time myself.
			 */
			static double scaled_clock;
			static void spawn_player();
			static sf::RenderWindow* window_ref;
		};
		//constexpr
		
	}
}
#endif
