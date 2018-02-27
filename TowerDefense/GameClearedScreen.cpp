#include "stdafx.h"
#include "GameClearedScreen.hpp"
#include "Align.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"
#include "Managers/GameManager.hpp"
#include "UIAssets.hpp"
#include "Player.hpp"
#include "SoundManager.hpp"
#include "SoundsAssets.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseButton> GameClearedScreen::menu_return_btn;
		std::unique_ptr<BaseText> GameClearedScreen::title_text;
		std::unique_ptr<BaseText> GameClearedScreen::score_text;

		void GameClearedScreen::init()
		{
			menu_return_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::quit_btn));
			title_text = std::make_unique<BaseText>(GlobalShared::get_trans().game_cleared_text);
			score_text = std::make_unique<BaseText>(GlobalShared::get_trans().score_text);
			Align::center(
				menu_return_btn->get_transformable(),
				sf::Vector2f(-menu_return_btn->get_sprite().getGlobalBounds().width/2.f, 70)
			);
			Align::center(
				title_text->get_transformable(),
				sf::Vector2f(-title_text->get_text().getGlobalBounds().width/2.f, -170)
			);
			Align::center(
				score_text->get_transformable(),
				sf::Vector2f(-score_text->get_text().getGlobalBounds().width / 2.f, -220)
			);
			close();
			menu_return_btn->on_click += Sharp::EventHandler::Bind(&GameClearedScreen::on_click_menu_return);
			menu_return_btn->auto_start();
			title_text->auto_start();
			score_text->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&GameClearedScreen::destroy);
		}

		void GameClearedScreen::open()
		{
			SoundManager::play_one_shoot(Constants::SoundsAssets::on_game_cleared);
			set_score_text(Managers::Player::get_score());
			menu_return_btn->isActive = true;
			title_text->isActive = true;
			score_text->isActive = true;
		}

		void GameClearedScreen::close()
		{
			menu_return_btn->isActive = false;
			title_text->isActive = false;
			score_text->isActive = false;
			Managers::Player::lose_score();
		}

		void GameClearedScreen::destroy()
		{
			menu_return_btn->on_click -= Sharp::EventHandler::Bind(&GameClearedScreen::on_click_menu_return);
			menu_return_btn.reset(nullptr);
			title_text.reset(nullptr);
			score_text.reset(nullptr);
		}

		void GameClearedScreen::on_click_menu_return()
		{
			close();
			Managers::GameManager::return_menu();
		}

		void GameClearedScreen::set_score_text(const unsigned int& value)
		{
			score_text->set_text(GlobalShared::get_trans().score_text + " " + std::to_string(value));
		}
	}
}
