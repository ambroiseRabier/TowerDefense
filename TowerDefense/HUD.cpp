#include "stdafx.h"
#include "Hud.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GlobalShared.hpp"
#include "UIAssets.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseText> Hud::level_text;
		std::unique_ptr<BaseText> Hud::money_text;
		std::unique_ptr<BaseText> Hud::wave_text;
		std::unique_ptr<BaseButton> Hud::pause_btn;
		std::unique_ptr<BaseButton> Hud::retry_btn;
		std::unique_ptr<BaseButton> Hud::up_speed_btn;

		std::string truncate(std::string str, size_t width, bool show_ellipsis=false)
		{
			if (str.length() > width)
				if (show_ellipsis)
					return str.substr(0, width) + "...";
				else
					return str.substr(0, width);
			return str;
		}

		void Hud::init()
		{
			level_text = std::make_unique<BaseText>("*Level");
			money_text = std::make_unique<BaseText>("*Money");
			wave_text = std::make_unique<BaseText>("*Wave");
			pause_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::pause_btn));
			retry_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::restart_btn));
			up_speed_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::speedUp_btn));
			Align::top_center(level_text->get_transformable(), sf::Vector2f(
				-200, 
				30
			));
			Align::top_center(money_text->get_transformable(), sf::Vector2f(
				200, 
				30
			));
			Align::top_center(wave_text->get_transformable(), sf::Vector2f(
				0, 
				60
			));
			Align::top_right(pause_btn->get_transformable(), sf::Vector2f(
				30 + pause_btn->get_sprite().getGlobalBounds().width, 
				30
			));
			Align::top_left(retry_btn->get_transformable(), sf::Vector2f(30, 30));
			Align::bottom_right(up_speed_btn->get_transformable(), sf::Vector2f(
				30 + up_speed_btn->get_sprite().getGlobalBounds().width, 
				30 + up_speed_btn->get_sprite().getGlobalBounds().height
			));
			close();
			pause_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_pause);
			retry_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_retry);
			up_speed_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_up_speed);
			level_text->auto_start();
			money_text->auto_start();
			wave_text->auto_start();
			pause_btn->auto_start();
			retry_btn->auto_start();
			up_speed_btn->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(Hud::destroy);
		}

		void Hud::destroy()
		{
			pause_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_pause);
			retry_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_retry);
			up_speed_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_up_speed);
			level_text.reset(nullptr);
			money_text.reset(nullptr);
			wave_text.reset(nullptr);
			pause_btn.reset(nullptr);
			retry_btn.reset(nullptr);
			up_speed_btn.reset(nullptr);
		}

		void Hud::open()
		{
			//todo: debug assert is inited.
			level_text->isActive = true;
			money_text->isActive = true;
			wave_text->isActive = true;
			pause_btn->isActive = true;
			retry_btn->isActive = true;
			up_speed_btn->isActive = true;
		}

		void Hud::close()
		{
			level_text->isActive = false;
			money_text->isActive = false;
			wave_text->isActive = false;
			pause_btn->isActive = false;
			retry_btn->isActive = false;
			up_speed_btn->isActive = false;
		}

		void Hud::set_level_text(const std::string& text)
		{
			level_text->set_text(text);
		}

		void Hud::set_money_text(const std::string& text)
		{
			money_text->set_text(truncate(text, text.find_first_of(".")+3));
		}

		void Hud::set_wave_text(const std::string& text)
		{
			wave_text->set_text(text);
		}

		void Hud::on_click_up_speed()
		{
			Managers::GameManager::up_game_speed();
		}

		void Hud::on_click_retry()
		{
			Managers::GameManager::restart_level();
		}

		void Hud::on_click_pause()
		{
			close();
			Managers::GameManager::pause();
		}
	}
}
