#pragma once
// to know : https://stackoverflow.com/questions/152555/h-or-hpp-for-your-class-definitions
#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include "Utils/Event.h"
#include "../../Player.hpp"
#include <memory>
#include "../../Tile.hpp"

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
			static const float get_game_speed();
			static float get_deltaTime();
			static Game::Player& get_player();
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
			static sf::RenderWindow* window_ref;
		};
		//constexpr
		
	}
}
#endif
