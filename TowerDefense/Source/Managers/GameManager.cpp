#include "stdafx.h"
#include "GameManager.hpp"
#include "../../Player.hpp"
#include "../../MenuScreen.hpp"
#include "../../PauseScreen.hpp"
#include "GameEngine/Debug.hpp"
#include "../../HUD.hpp"
#include "../../GameDesign.hpp"
#include "../../MapManager.hpp"
#include "../../GlobalShared.hpp"
#include "../../MapWaveManager.hpp"
#include "../../SetTimeout.hpp"

using namespace TowerDefense::GameEngine;
namespace TowerDefense 
{
	namespace Managers
	{
		GameState GameManager::state = GameState::Menu;
		float GameManager::deltaTime = 0.0;
		sf::Clock GameManager::clock;
		Sharp::Event<void> GameManager::on_update;
		unsigned int GameManager::game_speed_index;
		std::unique_ptr<Game::Player> GameManager::player;
		sf::RenderWindow* GameManager::window_ref;


		void GameManager::init(sf::RenderWindow* new_window_ref)
		{
			Debug::assert_m(!window_ref, "GameManager: window_ref has already been assigned ! (Please stop breaking the game intentionnaly)");
			window_ref = new_window_ref;
			game_speed_index = Constants::GameDesign::game_speed_default_index;
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&destroy);
		}

		void GameManager::destroy()
		{
			//GlobalShared::on_window_close -= Sharp::gEventHandler::Bind(&destroy);
			if (state == GameState::Pause || state == GameState::Playing)
			{
				MapManager::destroy_current_level();
			}
			//window_ref = nullptr; DONT DO THAT, or cna't close window.
			if (player.get()) {
				player.reset(nullptr);
			}
		}

		void GameManager::start()
		{
			UI::MenuScreen::open();
		}

		void GameManager::update()
		{
			deltaTime = clock.restart().asSeconds();
			// appeler delegate Update, metter pause ici.
			if (state != GameState::Pause)
			{
				on_update();
			}
		}
		
		void GameManager::start_level(const unsigned int& i)
		{
			Debug::info("GameManager: start_level " + std::to_string(i));
			// if was not already into a level.
			if (state != GameState::Playing)
			{
				state = GameState::Playing;
				spawn_player();
			}
			UI::HUD::open();
			MapManager::load_level(i);

			// add delay here ? to let the player prepare his stuff.
			MapWaveManager::start_wave_spawn();
		}

		void GameManager::restart_level()
		{
			state = GameState::Playing;
			Debug::log("GameManager: restart_level");
		}

		void GameManager::pause()
		{
			state = GameState::Pause;
			UI::PauseScreen::open();
			UI::HUD::close();
		}

		void GameManager::un_pause()
		{
			state = GameState::Playing;
			UI::PauseScreen::close();
			UI::HUD::open();
		}

		void GameManager::return_menu()
		{
			Debug::log("GameManager: return_menu");
			MapManager::destroy_current_level();
			player.reset(nullptr);
			UI::PauseScreen::close();
			UI::MenuScreen::open();
		}

		void GameManager::exit_game()
		{
			GlobalShared::on_window_close();
			Debug::log("this work ? up or down");
			GlobalShared::on_window_close_game_engine_pass();
			Debug::log("second");

			Debug::assert_m(window_ref, "GameManager: window_ref should never be null");
			window_ref->close();
		}

		void GameManager::up_game_speed()
		{
			Debug::log("GameManager: up_game_speed");
			const auto array_size = sizeof(Constants::GameDesign::game_speed_choices)/sizeof(*Constants::GameDesign::game_speed_choices);
			game_speed_index++;
			if (game_speed_index > array_size-1)
			{
				game_speed_index = 0;
			}
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

		Player& GameManager::get_player()
		{
			return *player;
		}

		const float GameManager::get_game_speed()
		{
			return Constants::GameDesign::game_speed_choices[game_speed_index];
		}
	}
}
