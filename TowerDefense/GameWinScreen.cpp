#include "stdafx.h"
#include "GameWinScreen.hpp"
#include "GlobalShared.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "BaseText.hpp"
#include "Config.hpp"
#include "UIAssets.hpp"
#include "Player.hpp"
#include "SoundManager.hpp"
#include "SoundsAssets.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> GameWinScreen::next_level_btn;
		std::unique_ptr<BaseButton> GameWinScreen::retry_btn;
		std::unique_ptr<BaseButton> GameWinScreen::menu_return_btn;
		std::unique_ptr<BaseText> GameWinScreen::title_text;
		std::unique_ptr<BaseText> GameWinScreen::score_text;

		void GameWinScreen::init()
		{
			next_level_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::next_level_btn));
			retry_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::restart_btn));
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::quit_btn));
			title_text = std::make_unique<BaseText>(Constants::Config::win_screen_text);
			score_text = std::make_unique<BaseText>(Constants::Config::score_text);

			Align::center(
				next_level_btn->get_transformable(),
				sf::Vector2f(-next_level_btn->get_sprite().getGlobalBounds().width/2.f, -70)
			);
			Align::center(
				retry_btn->get_transformable(),
				sf::Vector2f(-retry_btn->get_sprite().getGlobalBounds().width/2.f, 0)
			);
			Align::center(
				menu_return_btn->get_transformable(),
				sf::Vector2f(-menu_return_btn->get_sprite().getGlobalBounds().width/2.f, 70)
			);
			Align::center(
				title_text->get_transformable(),
				sf::Vector2f(-title_text->get_text().getGlobalBounds().width/2.f, -170)
			);
			Align::center(
				score_text->get_transformable(),
				sf::Vector2f(-score_text->get_text().getGlobalBounds().width / 2.f, -220)
			);
			close();
			next_level_btn->on_click += Sharp::EventHandler::Bind(&GameWinScreen::on_click_next_level);
			retry_btn->on_click += Sharp::EventHandler::Bind(&GameWinScreen::on_click_retry);
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&GameWinScreen::on_click_menu_return);
			next_level_btn->auto_start();
			retry_btn->auto_start();
			menu_return_btn->auto_start();
			title_text->auto_start();
			score_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&GameWinScreen::destroy);
		}

		void GameWinScreen::open()
		{
			SoundManager::play_one_shoot(Constants::SoundsAssets::on_game_win);
			set_score_text(Managers::Player::get_score());
			next_level_btn->isActive = true;
			retry_btn->isActive = true;
			menu_return_btn->isActive = true;
			title_text->isActive = true;
			score_text->isActive = true;
		}

		void GameWinScreen::close()
		{
			next_level_btn->isActive = false;
			retry_btn->isActive = false;
			menu_return_btn->isActive = false;
			title_text->isActive = false;
			score_text->isActive = false;
		}

		void GameWinScreen::destroy()
		{
			next_level_btn->on_click -= Sharp::EventHandler::Bind(&GameWinScreen::on_click_next_level);
			retry_btn->on_click -= Sharp::EventHandler::Bind(&GameWinScreen::on_click_retry);
			menu_return_btn->on_click -= Sharp::EventHandler::Bind(&GameWinScreen::on_click_menu_return);
			next_level_btn.reset(nullptr);
			retry_btn.reset(nullptr);
			menu_return_btn.reset(nullptr);
			title_text.reset(nullptr);
			score_text.reset(nullptr);
		}

		void GameWinScreen::on_click_next_level()
		{
			close();
			Managers::GameManager::start_next_level();
		}

		void GameWinScreen::on_click_retry()
		{
			close();
			Managers::GameManager::restart_level();
		}

		void GameWinScreen::on_click_menu_return()
		{
			close();
			Managers::GameManager::return_menu();
		}

		void GameWinScreen::set_score_text(const unsigned int& value)
		{
			score_text->set_text(Constants::Config::score_text + " " + std::to_string(value));
		}
	}
}
