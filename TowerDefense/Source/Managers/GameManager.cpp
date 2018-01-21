#include "stdafx.h"
#include "GameManager.hpp"
#include "Constants.hpp"
#include "../../Player.hpp"
#include "../../MenuScreen.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense 
{
	namespace Managers
	{
		GameState GameManager::state = GameState::Menu;
		float GameManager::deltaTime = 0.0;
		sf::Clock GameManager::clock;
		Sharp::Event<void> GameManager::on_update;
		unsigned int GameManager::game_speed_index;
		std::unique_ptr<Player> GameManager::player;
		sf::RenderWindow* GameManager::window_ref;

		void GameManager::start_level(int i)
		{
			Debug::info("GameManager: start_level " + std::to_string(i));
			if (state != GameState::Playing)
			{
				spawn_player();
			}
			state = GameState::Playing;
		}

		void GameManager::init(sf::RenderWindow* new_window_ref)
		{
			Debug::assert_m(!window_ref, "GameManager: window_ref has already been assigned ! (Please stop breaking the game intentionnaly)");
			window_ref = new_window_ref;
			game_speed_index = Constants::GameDesign::game_speed_default_index;
		}

		void GameManager::start()
		{
			UI::MenuScreen::open();
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

		void GameManager::return_menu()
		{
			player.reset(nullptr);
		}

		void GameManager::exit_game()
		{
			// in theory this will never be null when called.
			if (window_ref)
				window_ref->close();
		}

		void GameManager::spawn_player()
		{
			player = std::make_unique<Player>();
		}

		// region getter setter

		float GameManager::get_deltaTime () 
		{
			return deltaTime;
		}

		const float GameManager::get_game_speed()
		{
			return Constants::GameDesign::game_speed_choices[game_speed_index];
		}
	}
}
