#include "stdafx.h"
#include "PauseScreen.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GlobalShared.hpp"
#include "BaseText.hpp"
#include "Config.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> PauseScreen::resume_btn;
		std::unique_ptr<BaseButton> PauseScreen::resume_btn_2;
		std::unique_ptr<BaseButton> PauseScreen::menu_return_btn;
		std::unique_ptr<BaseText> PauseScreen::title_text;

		void PauseScreen::init()
		{
			resume_btn = std::make_unique<BaseButton>(GlobalShared::play_btn_texture);
			resume_btn_2 = std::make_unique<BaseButton>(GlobalShared::play_btn_texture);
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::quit_btn_texture);
			title_text = std::make_unique<BaseText>(Constants::Config::pause_text);
			Align::top_right(resume_btn->get_transformable(), sf::Vector2f(
				30 + resume_btn->get_sprite().getGlobalBounds().width, 
				30
			));
			Align::center(
				resume_btn_2->get_transformable(),
				sf::Vector2f(- resume_btn_2->get_sprite().getGlobalBounds().width/2.f, 0)
			);
			Align::center(
				menu_return_btn->get_transformable(),
				sf::Vector2f(- menu_return_btn->get_sprite().getGlobalBounds().width/2.f, 70)
			);
			Align::center(
				title_text->get_transformable(),
				sf::Vector2f(- title_text->get_text().getGlobalBounds().width/2.f, -170)
			);
			close();
			resume_btn->on_click += Sharp::EventHandler::Bind(&PauseScreen::on_click_resume);
			resume_btn_2->on_click += Sharp::EventHandler::Bind(&PauseScreen::on_click_resume);
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&PauseScreen::on_click_menu_return);
			resume_btn->auto_start();
			resume_btn_2->auto_start();
			menu_return_btn->auto_start();
			title_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&PauseScreen::destroy);
		}

		void PauseScreen::destroy()
		{
			resume_btn->on_click -= Sharp::EventHandler::Bind(&PauseScreen::on_click_resume);
			resume_btn_2->on_click -= Sharp::EventHandler::Bind(&PauseScreen::on_click_resume);
			menu_return_btn->on_click -= Sharp::EventHandler::Bind(&PauseScreen::on_click_menu_return);
			resume_btn.reset(nullptr);
			resume_btn_2.reset(nullptr);
			menu_return_btn.reset(nullptr);
			title_text.reset(nullptr);
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
			resume_btn_2->isActive = true;
			menu_return_btn->isActive = true;
			title_text->isActive = true;
		}

		void PauseScreen::close()
		{
			resume_btn->isActive = false;
			resume_btn_2->isActive = false;
			menu_return_btn->isActive = false;
			title_text->isActive = false;
		}
	}
}
