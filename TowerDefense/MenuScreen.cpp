#include "stdafx.h"
#include "MenuScreen.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GlobalShared.hpp"
#include "Hud.hpp"
#include "Config.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> MenuScreen::play_btn;
		std::unique_ptr<BaseButton> MenuScreen::quit_btn;
		std::unique_ptr<BaseText> MenuScreen::title_text;

		void MenuScreen::init()
		{
			play_btn = std::make_unique<BaseButton>(GlobalShared::play_btn_texture);
			quit_btn = std::make_unique<BaseButton>(GlobalShared::quit_btn_texture);
			title_text = std::make_unique<BaseText>(Constants::Config::game_name);
			Align::center(
				play_btn->get_transformable(), 
				sf::Vector2f(-play_btn->get_sprite().getGlobalBounds().width/2.f, 0)
			);
			Align::center(
				quit_btn->get_transformable(), 
				sf::Vector2f(-quit_btn->get_sprite().getGlobalBounds().width/2.f, 70)
			);
			Align::center(
				title_text->get_transformable(),
				sf::Vector2f(- title_text->get_text().getGlobalBounds().width/2.f, -170)
			);
			close();
			play_btn->on_click += Sharp::EventHandler::Bind(&MenuScreen::on_click_play);
			quit_btn->on_click += Sharp::EventHandler::Bind(&MenuScreen::on_click_quit);
			play_btn->auto_start();
			quit_btn->auto_start();
			title_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&MenuScreen::destroy);
		}

		void MenuScreen::destroy()
		{
			play_btn->on_click -= Sharp::EventHandler::Bind(&MenuScreen::on_click_play);
			play_btn.reset(nullptr);
			title_text.reset(nullptr);
			//You cannot do that here, because otherwise it is destroyed when the delagate iterate it's function
			// the simplest solution is to destroy the quit_btn after everything.
			//quit_btn.reset(nullptr); 
			// don't remove event to on_click either.
		}

		void MenuScreen::on_click_play()
		{
			close();
			Managers::GameManager::start_level(0);
		}

		void MenuScreen::on_click_quit()
		{
			Managers::GameManager::exit_game();
		}

		void MenuScreen::open()
		{
			play_btn->isActive = true;
			quit_btn->isActive = true;
			title_text->isActive = true;
		}

		void MenuScreen::close()
		{
			play_btn->isActive = false;
			quit_btn->isActive = false;
			title_text->isActive = false;
		}

		void MenuScreen::destroy_quit_btn()
		{
			quit_btn->on_click -= Sharp::EventHandler::Bind(&MenuScreen::on_click_quit);
			quit_btn.reset(nullptr); 
		}
	}
}
