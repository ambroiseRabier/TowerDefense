#include "stdafx.h"
#include "GameManager.hpp"
#include "../../Player.hpp"
#include "../../MenuScreen.hpp"
#include "../../PauseScreen.hpp"
#include "GameEngine/Debug.hpp"
#include "../../Hud.hpp"
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
		float GameManager::fixed_delta_time = 0.0f;
		float GameManager::delta_time = 0.0f;
		sf::Clock GameManager::clock;
		double GameManager::scaled_clock = 0;
		Sharp::Event<void> GameManager::on_update;
		unsigned int GameManager::game_speed_index;
		unsigned int GameManager::level_index = 0;
		sf::RenderWindow* GameManager::window_ref;


		void GameManager::init(sf::RenderWindow* new_window_ref)
		{
			Debug::assert_m(!window_ref, "GameManager: window_ref has already been assigned ! (Please stop breaking the game intentionnaly)");
			window_ref = new_window_ref;
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&destroy);
		}

		void GameManager::destroy()
		{
			//GlobalShared::on_window_close -= Sharp::gEventHandler::Bind(&destroy);
			if (state == GameState::Pause || state == GameState::Playing)
			{
				MapManager::destroy_current_level();
			}
			//window_ref = nullptr; DONT DO THAT, or you can't close window.
		}

		void GameManager::start()
		{
			UI::MenuScreen::open();
		}

		void GameManager::update()
		{
			fixed_delta_time = clock.restart().asSeconds();
			delta_time = fixed_delta_time * get_game_speed();
			if (state != GameState::Pause)
			{
				scaled_clock += delta_time;
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
			}
			level_index = i;
			game_speed_index = 0;
			UI::Hud::open(); // if next level then hud already here, this is useless, unless there is a winscreen.
			MapManager::load_level(level_index);
			Player::start();
			// add delay here ? to let the player prepare his stuff.
			MapWaveManager::start();
		}

		void GameManager::restart_level()
		{
			assert(state == GameState::Playing);
			assert(level_index >= 0);
			MapManager::destroy_current_level();
			start_level(level_index);
		}

		void GameManager::pause()
		{
			UI::PauseScreen::open();
			UI::Hud::close();
			state = GameState::Pause;
		}

		void GameManager::un_pause()
		{
			UI::PauseScreen::close();
			UI::Hud::open();
			state = GameState::Playing;
		}

		void GameManager::return_menu()
		{
			MapManager::destroy_current_level();
			UI::PauseScreen::close();
			UI::MenuScreen::open();
			state = GameState::Menu;
		}

		void GameManager::exit_game()
		{
			GlobalShared::on_window_close();
 			GlobalShared::on_window_close_game_engine_pass();
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

		// region getter setter

		const float& GameManager::get_fixed_delta_time() 
		{
			return fixed_delta_time;
		}

		const float& GameManager::get_delta_time()
		{
			return delta_time;
		}

		const double& GameManager::get_clock()
		{
			return scaled_clock;
		}

		const sf::Clock& GameManager::get_fixed_clock()
		{
			return clock;
		}

		const float& GameManager::get_game_speed()
		{
			return Constants::GameDesign::game_speed_choices[game_speed_index];
		}
	}
}
