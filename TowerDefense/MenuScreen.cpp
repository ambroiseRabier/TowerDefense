#include "stdafx.h"
#include "MenuScreen.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GameEngine/Debug.hpp"
#include "GlobalShared.hpp"
#include "HUD.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> MenuScreen::play_btn;
		std::unique_ptr<BaseButton> MenuScreen::quit_btn;

		void MenuScreen::init()
		{
			play_btn = std::make_unique<BaseButton>(GlobalShared::play_btn_texture);
			quit_btn = std::make_unique<BaseButton>(GlobalShared::quit_btn_texture);
			Align::center(play_btn->get_transformable(), sf::Vector2f(0, -100));
			Align::center(quit_btn->get_transformable(), sf::Vector2f(0, 100));
			close();
			play_btn->on_click += Sharp::EventHandler::Bind(&MenuScreen::on_click_play);
			quit_btn->on_click += Sharp::EventHandler::Bind(&MenuScreen::on_click_quit);
			play_btn->auto_start();
			quit_btn->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&destroy);
		}

		void MenuScreen::destroy()
		{
			//GlobalShared::on_window_close -= Sharp::EventHandler::Bind(&destroy);
			play_btn.reset(nullptr);
			quit_btn.reset(nullptr);
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
		}

		void MenuScreen::close()
		{
			play_btn->isActive = false;
			quit_btn->isActive = false;
		}

	}
}
