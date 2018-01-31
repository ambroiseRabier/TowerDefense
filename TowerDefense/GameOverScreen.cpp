#include "stdafx.h"
#include "GameOverScreen.hpp"
#include "GlobalShared.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "BaseText.hpp"
#include "Config.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> GameOverScreen::retry_btn;
		std::unique_ptr<BaseButton> GameOverScreen::menu_return_btn;
		std::unique_ptr<BaseText> GameOverScreen::title_text;

		void GameOverScreen::init()
		{
			retry_btn = std::make_unique<BaseButton>(GlobalShared::restart_btn_texture);
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::quit_btn_texture);
			title_text = std::make_unique<BaseText>(Constants::Config::game_over_screen_text);
			Align::center(
				retry_btn->get_transformable(),
				sf::Vector2f(-retry_btn->get_sprite().getGlobalBounds().width/2.f,  0)
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
			retry_btn->on_click += Sharp::EventHandler::Bind(&GameOverScreen::on_click_retry);
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&GameOverScreen::on_click_menu_return);
			retry_btn->auto_start();
			menu_return_btn->auto_start();
			title_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&GameOverScreen::destroy);
		}

		void GameOverScreen::open()
		{
			retry_btn->isActive = true;
			menu_return_btn->isActive = true;
			title_text->isActive = true;
		}

		void GameOverScreen::close()
		{
			retry_btn->isActive = false;
			menu_return_btn->isActive = false;
			title_text->isActive = false;
		}

		void GameOverScreen::destroy()
		{
			retry_btn->on_click -= Sharp::EventHandler::Bind(&GameOverScreen::on_click_retry);
			menu_return_btn->on_click -= Sharp::EventHandler::Bind(&GameOverScreen::on_click_menu_return);
			retry_btn.reset(nullptr);
			menu_return_btn.reset(nullptr);
			title_text.reset(nullptr);
		}

		void GameOverScreen::on_click_retry()
		{
			close();
			Managers::GameManager::restart_level();
		}

		void GameOverScreen::on_click_menu_return()
		{
			close();
			Managers::GameManager::return_menu();
		}
	}
}
