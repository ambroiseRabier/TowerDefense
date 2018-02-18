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
#include "../../LevelDesign.hpp"
#include "../../GameOverScreen.hpp"
#include "../../GameWinScreen.hpp"
#include "../../GameClearedScreen.hpp"
#include "../../Timer.hpp"
#include "../../SoundManager.hpp"
#include "../../SoundsAssets.hpp"

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
		Sharp::Event<void> GameManager::on_update_after_collision;
		unsigned int GameManager::game_speed_index;
		unsigned int GameManager::level_index = 0;
		sf::RenderWindow* GameManager::window_ref;
		unsigned int GameManager::start_wave_time_out_id = 0;


		void GameManager::init(sf::RenderWindow* new_window_ref)
		{
			Debug::assert_m(!window_ref, "GameManager: window_ref has already been assigned ! (Please stop breaking the game intentionnaly)");
			window_ref = new_window_ref;
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

		void GameManager::update_after_collision()
		{
			if (state != GameState::Pause)
			{
				on_update_after_collision();
			}
		}

		void GameManager::start_next_level()
		{
			start_level(++level_index);
		}
		
		void GameManager::start_level(const unsigned int& i)
		{
			Debug::assert_m(
				i >= 0 && i < GlobalShared::level_design.map_array.size(),
				"GameManager: trying to start a level that do not exist ! index of level: " + std::to_string(i)
			);
			Debug::info("GameManager: start_level " + std::to_string(i));
			// if was not already into a level.
			if (state != GameState::Playing)
			{
				state = GameState::Playing;
				// that mean the music won't restart when you press restart in outside pause.
				SoundManager::start_music(Constants::SoundsAssets::game_loop);
			}
			level_index = i;
			game_speed_index = 0;
			UI::Hud::open(); // if next level then hud already here, this is useless, unless there is a winscreen.
			MapManager::load_level(GlobalShared::level_design.map_array.at(level_index));
			Player::start();
			const auto start_wave_delay = GlobalShared::level_design.map_array.at(level_index).preparation_time;
			UI::Hud::start_count_down(start_wave_delay);
			start_wave_time_out_id = Utils::Timer::set_time_out(
				Sharp::EventHandler::Bind(&GameManager::start_wave),
				static_cast<float>(start_wave_delay)
			);
		}

		void GameManager::start_wave()
		{
			start_wave_time_out_id = 0;
			MapWaveManager::start();
			SoundManager::play_one_shoot(Constants::SoundsAssets::start_spawn_minion);
		}

		void GameManager::restart_level()
		{
			assert(state == GameState::Playing || state == GameState::Pause);
			if (start_wave_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(start_wave_time_out_id);
			}
			MapManager::destroy_current_level();
			start_level(level_index);
		}

		void GameManager::pause()
		{
			UI::PauseScreen::open();
			state = GameState::Pause;
			// reducing music volume sounds better then pausing music I think. 
			// Bug: if sound volume is inferior to pause_music volume
			SoundManager::set_current_music_volume(Constants::SoundsAssets::pause_music_volume);
		}

		void GameManager::un_pause()
		{
			UI::Hud::open();
			state = GameState::Playing;
			SoundManager::set_default_music_volume();
		}

		void GameManager::return_menu()
		{
			if (start_wave_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(start_wave_time_out_id);
			}
			MapManager::destroy_current_level();
			UI::MenuScreen::open();
			state = GameState::Menu;
			SoundManager::stop_music();
			Player::lose_score();
		}

		void GameManager::exit_game()
		{
			if (start_wave_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(start_wave_time_out_id);
			}
			if (state == GameState::Pause || state == GameState::Playing)
			{
				MapManager::destroy_current_level();
			}
			GlobalShared::on_window_close();
 			GlobalShared::on_window_close_game_engine_pass();
			Debug::assert_m(window_ref, "GameManager: window_ref should never be null");
			window_ref->close();
		}

		void GameManager::up_game_speed()
		{
			Debug::log("GameManager: up_game_speed");
			//const auto array_size = sizeof(Constants::GameDesign::game_speed_choices)/sizeof(*Constants::GameDesign::game_speed_choices);
			game_speed_index++;
			if (game_speed_index > GlobalShared::get_gd().game_speed_choices.size()-1)
			{
				game_speed_index = 0;
			}
			const auto array_size_pitch = sizeof(Constants::SoundsAssets::game_speed_pitch_choices)/sizeof(*Constants::SoundsAssets::game_speed_pitch_choices);

			Debug::assert_m(
				GlobalShared::get_gd().game_speed_choices.size() == array_size_pitch, 
				"Constants::SoundsAssets::game_speed_pitch_choices and Constants::GameDesign::game_speed_choices need to have the same size !"
			);
			SoundManager::set_current_music_pitch(
				Constants::SoundsAssets::game_speed_pitch_choices[game_speed_index]
			);
		}

		void GameManager::game_over()
		{
			// might need to keep state to playing if we wnat minion to do something funny
			Player::on_game_over();
			UI::Hud::close();
			state = GameState::Pause;
			SoundManager::stop_music();
			UI::GameOverScreen::open();
		}

		void GameManager::game_win()
		{
			// might need to keep state to playing if we wnat minion to do something funny
			state = GameState::Pause;
			SoundManager::stop_music();
			Player::on_game_win();
			UI::Hud::close();
			const bool was_last_level = level_index >= GlobalShared::level_design.map_array.size()-1;
			if (was_last_level)
			{
				UI::GameClearedScreen::open();
			} 
			else
			{
				UI::GameWinScreen::open();
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
			return GlobalShared::get_gd().game_speed_choices[game_speed_index];
		}
	}
}
