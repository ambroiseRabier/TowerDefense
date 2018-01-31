#include "stdafx.h"
#include "GameWinScreen.hpp"
#include "GlobalShared.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "BaseText.hpp"
#include "Config.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> GameWinScreen::next_level_btn;
		std::unique_ptr<BaseButton> GameWinScreen::retry_btn;
		std::unique_ptr<BaseButton> GameWinScreen::menu_return_btn;
		std::unique_ptr<BaseText> GameWinScreen::title_text;


		void GameWinScreen::init()
		{
			next_level_btn = std::make_unique<BaseButton>(GlobalShared::next_level_btn_texture);
			retry_btn = std::make_unique<BaseButton>(GlobalShared::restart_btn_texture);
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::quit_btn_texture);
			title_text = std::make_unique<BaseText>(Constants::Config::win_screen_text);
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
			close();
			next_level_btn->on_click += Sharp::EventHandler::Bind(&GameWinScreen::on_click_next_level);
			retry_btn->on_click += Sharp::EventHandler::Bind(&GameWinScreen::on_click_retry);
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&GameWinScreen::on_click_menu_return);
			next_level_btn->auto_start();
			retry_btn->auto_start();
			menu_return_btn->auto_start();
			title_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&GameWinScreen::destroy);
		}

		void GameWinScreen::open()
		{
			next_level_btn->isActive = true;
			retry_btn->isActive = true;
			menu_return_btn->isActive = true;
			title_text->isActive = true;
		}

		void GameWinScreen::close()
		{
			next_level_btn->isActive = false;
			retry_btn->isActive = false;
			menu_return_btn->isActive = false;
			title_text->isActive = false;
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
	}
}
