#include "GameManager.hpp"
#include "stdafx.h"

namespace TowerDefense 
{
	namespace Managers
	{
		GameState GameManager::state = GameState::Menu;
		float GameManager::deltaTime = 0.0;
		sf::Clock GameManager::clock;

		void GameManager::StartLevel(int i)
		{
		}

		void GameManager::Init()
		{
			
		}

		void GameManager::update()
		{
			deltaTime = clock.restart().asSeconds();
			// appeler delegate Update, metter pause ici.
		}

		void GameManager::RestartLevel()
		{

		}

		// region getter setter

		float GameManager::get_deltaTime () 
		{
			return deltaTime;
		}
	}
}
