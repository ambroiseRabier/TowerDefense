#include "stdafx.h"
#include "GameManager.hpp"

namespace TowerDefense 
{
	namespace Managers
	{
		GameState GameManager::state = GameState::Menu;
		float GameManager::deltaTime = 0.0;
		sf::Clock GameManager::clock;
		Sharp::Event<void> GameManager::on_update;

		void GameManager::start_level(int i)
		{
			state = GameState::Playing;
		}

		void GameManager::init()
		{
			
		}

		void GameManager::update()
		{
			deltaTime = clock.restart().asSeconds();
			// appeler delegate Update, metter pause ici.
			on_update();
		}

		void GameManager::restart_level()
		{
			state = GameState::Playing;
		}

		void GameManager::pause()
		{
			state = GameState::Pause;
		}

		void GameManager::un_pause()
		{
			state = GameState::Playing;
		}

		// region getter setter

		float GameManager::get_deltaTime () 
		{
			return deltaTime;
		}
	}
}
