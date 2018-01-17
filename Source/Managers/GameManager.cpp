#include "GameManager.hpp"
#include "stdafx.h"

namespace TowerDefense 
{
	namespace Managers
	{
		GameState GameManager::state = GameState::Menu;
		float GameManager::deltaTime = 0.0;
		sf::Clock GameManager::clock;
		Sharp::Event<void> GameManager::on_update;

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
			on_update();
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
