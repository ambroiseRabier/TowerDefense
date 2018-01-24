#include "stdafx.h"
#include "PauseScreen.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> PauseScreen::resume_btn;
		std::unique_ptr<BaseButton> PauseScreen::menu_return_btn;

		void PauseScreen::init()
		{
			resume_btn = std::make_unique<BaseButton>(GlobalShared::play_btn_texture);
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::quit_btn_texture);
			Align::center(resume_btn->get_transformable(), sf::Vector2f(0, -50));
			Align::center(menu_return_btn->get_transformable(), sf::Vector2f(0, 50));
			close();
			resume_btn->on_click += Sharp::EventHandler::Bind(&PauseScreen::on_click_resume);
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&PauseScreen::on_click_menu_return);
			resume_btn->auto_start();
			menu_return_btn->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&destroy);
		}

		void PauseScreen::destroy()
		{
			//GlobalShared::on_window_close -= Sharp::EventHandler::Bind(&destroy);
			resume_btn.reset(nullptr);
			menu_return_btn.reset(nullptr);
		}

		void PauseScreen::on_click_resume()
		{
			Managers::GameManager::un_pause();
		}
		void PauseScreen::on_click_menu_return()
		{
			Managers::GameManager::return_menu();
		}

		void PauseScreen::open()
		{
			resume_btn->isActive = true;
			menu_return_btn->isActive = true;
		}

		void PauseScreen::close()
		{
			resume_btn->isActive = false;
			menu_return_btn->isActive = false;
		}
	}
}
