#include "stdafx.h"
#include "WinScreen.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GameEngine/Debug.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> WinScreen::menu_return_btn;

		void WinScreen::init()
		{
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::play_btn_texture);
			Align::center(menu_return_btn->get_transformable(), sf::Vector2f(100, 100));
			close();
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&WinScreen::on_click_menu_return);
			menu_return_btn->auto_start();
		}

		void WinScreen::on_click_menu_return()
		{
			Managers::GameManager::return_menu();
		}

		void WinScreen::open()
		{
			menu_return_btn->isActive = true;
		}

		void WinScreen::close()
		{
			menu_return_btn->isActive = false;
		}
	}
}
