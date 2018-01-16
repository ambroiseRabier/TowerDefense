#pragma once
// to know : https://stackoverflow.com/questions/152555/h-or-hpp-for-your-class-definitions
#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include <SFML/System/Clock.hpp>

namespace TowerDefense
{
	namespace Managers
	{
		enum class GameState { Menu, Playing, Pause };
		class GameManager
		{
		public:
			//GameManager() {}
			//~GameManager() {}
			static void StartLevel(int i);
			static void Init();
			static void Update();
			static float get_deltaTime(); // const :'(, static do not take const
			static void RestartLevel();
			static GameState state;
		private:
			static float deltaTime;
			static sf::Clock clock;
		};
		//constexpr
		
	}
}
#endif
