#include "stdafx.h"
#include "GameClearedScreen.hpp"
#include "Align.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"
#include "Managers/GameManager.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> GameClearedScreen::menu_return_btn;
		std::unique_ptr<BaseText> GameClearedScreen::title_text;

		void GameClearedScreen::init()
		{
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::quit_btn_texture);
			title_text = std::make_unique<BaseText>(Constants::Config::game_cleared_text);
			Align::center(
				menu_return_btn->get_transformable(),
				sf::Vector2f(-menu_return_btn->get_sprite().getGlobalBounds().width/2.f, 70)
			);
			Align::center(
				title_text->get_transformable(),
				sf::Vector2f(-title_text->get_text().getGlobalBounds().width/2.f, -170)
			);
			close();
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&GameClearedScreen::on_click_menu_return);
			menu_return_btn->auto_start();
			title_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&GameClearedScreen::destroy);
		}

		void GameClearedScreen::open()
		{
			menu_return_btn->isActive = true;
			title_text->isActive = true;
		}

		void GameClearedScreen::close()
		{
			menu_return_btn->isActive = false;
			title_text->isActive = false;
		}

		void GameClearedScreen::destroy()
		{
			menu_return_btn->on_click -= Sharp::EventHandler::Bind(&GameClearedScreen::on_click_menu_return);
			menu_return_btn.reset(nullptr);
			title_text.reset(nullptr);
		}

		void GameClearedScreen::on_click_menu_return()
		{
			close();
			Managers::GameManager::return_menu();
		}
	}
}
