#include "stdafx.h"
#include "GameManager.hpp"
#include "Constants.hpp"

namespace TowerDefense 
{
	namespace Managers
	{
		GameState GameManager::state = GameState::Menu;
		float GameManager::deltaTime = 0.0;
		sf::Clock GameManager::clock;
		Sharp::Event<void> GameManager::on_update;
		unsigned int GameManager::game_speed_index;

		void GameManager::start_level(int i)
		{
			state = GameState::Playing;
		}

		void GameManager::init()
		{
			game_speed_index = Constants::GameDesign::game_speed_default_index;
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

		const float GameManager::get_game_speed()
		{
			return Constants::GameDesign::game_speed_choices[game_speed_index];
		}

		// region getter setter

		float GameManager::get_deltaTime () 
		{
			return deltaTime;
		}
	}
}
