#pragma once
// to know : https://stackoverflow.com/questions/152555/h-or-hpp-for-your-class-definitions
#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include <SFML/System/Clock.hpp>
#include "../../TowerDefense/Event.h"

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
			static void StartLevel(int i);
			static void Init();
			static void update();
			static float get_deltaTime(); // const :'(, static do not take const
			static void RestartLevel();
			static void pause();
			static GameState state;
		private:
			static float deltaTime;
			static sf::Clock clock;
		};
		//constexpr
		
	}
}
#endif
