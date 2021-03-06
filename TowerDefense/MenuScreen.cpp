#include "stdafx.h"
#include "MenuScreen.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GlobalShared.hpp"
#include "Hud.hpp"
#include "Config.hpp"
#include "UIAssets.hpp"
#include "GameEngine/DisplayManager.hpp"
#include "Assets.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<GameObject> MenuScreen::background;
		std::unique_ptr<BaseButton> MenuScreen::play_btn;
		std::unique_ptr<BaseButton> MenuScreen::quit_btn;
		std::unique_ptr<BaseText> MenuScreen::title_text;
		std::unique_ptr<BaseText> MenuScreen::credits_text;

		void MenuScreen::init()
		{
			background = std::make_unique<GameObject>(
				std::make_shared<sf::Sprite>(*GlobalShared::get_texture(Constants::Assets::menu_background)),
				Constants::ZIndex::ui_background
			);
			UI::Align::center(
				background->get_transformable(),
				sf::Vector2f(
					-static_cast<float>(GlobalShared::get_texture(Constants::Assets::menu_background)->getSize().x)/2.f,
					-static_cast<float>(GlobalShared::get_texture(Constants::Assets::menu_background)->getSize().y)/2.f
				)
			);
			DisplayManager::addChild(*background);
			play_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::play_btn));
			quit_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::quit_btn));
			title_text = std::make_unique<BaseText>(Constants::Config::game_name);
			credits_text = std::make_unique<BaseText>(GlobalShared::get_trans().credits);
			Align::center(
				play_btn->get_transformable(), 
				sf::Vector2f(-play_btn->get_sprite().getGlobalBounds().width/2.f, -50)
			);
			Align::center(
				quit_btn->get_transformable(), 
				sf::Vector2f(-quit_btn->get_sprite().getGlobalBounds().width/2.f, 170)
			);
			Align::center(
				title_text->get_transformable(),
				sf::Vector2f(- title_text->get_text().getGlobalBounds().width/2.f, -170)
			);
			Align::bottom_right(
				credits_text->get_transformable(),
				sf::Vector2f(
					credits_text->get_text().getGlobalBounds().width + 30,
					credits_text->get_text().getGlobalBounds().height + 30
				)
			);
			close();
			play_btn->on_click += Sharp::EventHandler::Bind(&MenuScreen::on_click_play);
			quit_btn->on_click += Sharp::EventHandler::Bind(&MenuScreen::on_click_quit);
			play_btn->auto_start();
			quit_btn->auto_start();
			title_text->auto_start();
			credits_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&MenuScreen::destroy);
		}

		void MenuScreen::destroy()
		{
			play_btn->on_click -= Sharp::EventHandler::Bind(&MenuScreen::on_click_play);
			DisplayManager::remove_child(*background);
			background.reset(nullptr);
			play_btn.reset(nullptr);
			title_text.reset(nullptr);
			credits_text.reset(nullptr);
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
			credits_text->isActive = true;
			background->isActive = true;
		}

		void MenuScreen::close()
		{
			play_btn->isActive = false;
			quit_btn->isActive = false;
			title_text->isActive = false;
			credits_text->isActive = false;
			background->isActive = false;
		}

		void MenuScreen::destroy_quit_btn()
		{
			quit_btn->on_click -= Sharp::EventHandler::Bind(&MenuScreen::on_click_quit);
			quit_btn.reset(nullptr); 
		}
	}
}
