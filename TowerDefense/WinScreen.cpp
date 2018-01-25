#include "stdafx.h"
#include "WinScreen.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GameEngine/Debug.hpp"
#include "GlobalShared.hpp"

using namespace sf;

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> WinScreen::menu_return_btn;

		void WinScreen::init()
		{
			score = 0;
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::play_btn_texture);
			Align::center(menu_return_btn->get_transformable(), sf::Vector2f(100, 100));
			close();
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&WinScreen::on_click_menu_return);
			menu_return_btn->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&destroy);
		}

		void WinScreen::on_click_menu_return()
		{
			Managers::GameManager::return_menu();
		}

		void WinScreen::setScore(int pScore) {
			score = pScore;
		}

		void WinScreen::createText() {
			Text gameover_text("Game Over", *GlobalShared::default_font);
			gameover_text.setCharacterSize(60);
			gameover_text.setStyle(Text::Bold);
			gameover_text.setFillColor(Color::Red);
			gameover_text.setOutlineColor(Color::Blue);
			gameover_text.setPosition(200, 100);

			String lString = std::to_string(score);
			Text score_text("Score : " + lString, *GlobalShared::default_font);
			score_text.setCharacterSize(30);
			score_text.setStyle(Text::Bold);
			score_text.setFillColor(Color::Red);
			score_text.setOutlineColor(Color::Blue);
			gameover_text.setPosition(200, 150);
		}

		void WinScreen::destroy()
		{
			menu_return_btn.reset(nullptr);
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
