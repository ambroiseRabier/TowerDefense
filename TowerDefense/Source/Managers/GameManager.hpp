#pragma once
// to know : https://stackoverflow.com/questions/152555/h-or-hpp-for-your-class-definitions
#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include "Utils/Event.h"
#include "../../Player.hpp"
#include <memory>

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
			static void start_level(int i);
			static void init();
			static void start();
			static void update();
			static void restart_level();
			static void pause();
			static void un_pause();
			static void return_menu();
			static GameState state;
			static const float get_game_speed();
			static float get_deltaTime(); // const :'(, static do not take const
		private:
			/**
			 * \brief 
			 * Speed the turret and minions.
			 */
			static unsigned int game_speed_index;
			static std::unique_ptr<Game::Player> player;
			static float deltaTime;
			static sf::Clock clock;
			static void spawn_player();

		};
		//constexpr
		
	}
}
#endif
