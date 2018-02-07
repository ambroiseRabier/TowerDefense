#include "stdafx.h"
#include "Hud.hpp"
#include "Align.hpp"
#include "Managers/GameManager.hpp"
#include "GlobalShared.hpp"
#include "UIAssets.hpp"
#include "Player.hpp"
#include "Timer.hpp"

namespace TowerDefense
{
	namespace UI
	{
		std::unique_ptr<BaseText> Hud::level_text;
		std::unique_ptr<BaseText> Hud::money_text;
		std::unique_ptr<BaseText> Hud::wave_text;
		std::unique_ptr<BaseText> Hud::help_tower_text;
		std::unique_ptr<BaseText> Hud::count_down_text;
		std::unique_ptr<BaseText> Hud::score_text;
		std::unique_ptr<BaseButton> Hud::pause_btn;
		std::unique_ptr<BaseButton> Hud::retry_btn;
		std::unique_ptr<BaseButton> Hud::up_speed_btn;
		std::unique_ptr<BaseButton> Hud::stone_tower_btn;
		std::unique_ptr<BaseButton> Hud::freeze_tower_btn;
		std::unique_ptr<BaseButton> Hud::explosiv_tower_btn;
		unsigned int Hud::preparation_time_remaining;
		unsigned int Hud::count_down_time_out_id;
		bool Hud::count_down_active;

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
			score_text = std::make_unique<BaseText>("*Score");
			help_tower_text = std::make_unique<BaseText>(Constants::Config::help_tower_build_text);
			count_down_text = std::make_unique<BaseText>("3", 108);
			pause_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::pause_btn));
			retry_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::restart_btn));
			up_speed_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::speedUp_btn));
			stone_tower_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::stone_tower_btn));
			freeze_tower_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::freeze_tower_btn));
			explosiv_tower_btn = std::make_unique<BaseButton>(GlobalShared::get_texture(Constants::UIAssets::explosiv_tower_btn));
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
			Align::bottom_center(help_tower_text->get_transformable(), sf::Vector2f(
				0 - help_tower_text->get_text().getGlobalBounds().width/2, 
				30 + help_tower_text->get_text().getGlobalBounds().height
			));
			Align::center(count_down_text->get_transformable(), sf::Vector2f(
				- count_down_text->get_text().getGlobalBounds().width/2, 
				- count_down_text->get_text().getGlobalBounds().height
			));
			Align::top_left(score_text->get_transformable(), sf::Vector2f(100, 30));
			Align::top_right(pause_btn->get_transformable(), sf::Vector2f(
				30 + pause_btn->get_sprite().getGlobalBounds().width, 
				30
			));
			Align::top_left(retry_btn->get_transformable(), sf::Vector2f(30, 30));

			Align::bottom_right(up_speed_btn->get_transformable(), sf::Vector2f(
				30 + up_speed_btn->get_sprite().getGlobalBounds().width, 
				30 + up_speed_btn->get_sprite().getGlobalBounds().height
			));
			Align::bottom_center(stone_tower_btn->get_transformable(), sf::Vector2f(
				-100,
				30 + stone_tower_btn->get_sprite().getGlobalBounds().height
			));
			Align::bottom_center(freeze_tower_btn->get_transformable(), sf::Vector2f(
				0,
				30 + freeze_tower_btn->get_sprite().getGlobalBounds().height
			));
			Align::bottom_center(explosiv_tower_btn->get_transformable(), sf::Vector2f(
				100,
				30 + explosiv_tower_btn->get_sprite().getGlobalBounds().height
			));
			close();
			pause_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_pause);
			retry_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_retry);
			up_speed_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_up_speed);
			stone_tower_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_stone);
			freeze_tower_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_freeze);
			explosiv_tower_btn->on_click += Sharp::EventHandler::Bind(&Hud::on_click_explosiv);
			level_text->auto_start();
			money_text->auto_start();
			wave_text->auto_start();
			score_text->auto_start();
			help_tower_text->auto_start();
			count_down_text->auto_start();
			pause_btn->auto_start();
			retry_btn->auto_start();
			up_speed_btn->auto_start();
			stone_tower_btn->auto_start();
			freeze_tower_btn->auto_start();
			explosiv_tower_btn->auto_start();
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(Hud::destroy);
		}

		void Hud::destroy()
		{
			if (count_down_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(count_down_time_out_id);
				count_down_time_out_id = 0;
			}
			pause_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_pause);
			retry_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_retry);
			up_speed_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_up_speed);
			stone_tower_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_stone);
			freeze_tower_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_freeze);
			explosiv_tower_btn->on_click -= Sharp::EventHandler::Bind(&Hud::on_click_explosiv);
			level_text.reset(nullptr);
			money_text.reset(nullptr);
			wave_text.reset(nullptr);
			score_text.reset(nullptr);
			help_tower_text.reset(nullptr);
			count_down_text.reset(nullptr);
			pause_btn.reset(nullptr);
			retry_btn.reset(nullptr);
			up_speed_btn.reset(nullptr);
			stone_tower_btn.reset(nullptr);
			freeze_tower_btn.reset(nullptr);
			explosiv_tower_btn.reset(nullptr);
		}

		void Hud::open()
		{
			//todo: debug assert is inited.
			level_text->isActive = true;
			money_text->isActive = true;
			wave_text->isActive = true;
			score_text->isActive = true;
			help_tower_text->isActive = false; // note: false here
			count_down_text->isActive = count_down_active;
			pause_btn->isActive = true;
			retry_btn->isActive = true;
			up_speed_btn->isActive = true;
			stone_tower_btn->isActive = true;
			freeze_tower_btn->isActive = true;
			explosiv_tower_btn->isActive = true;
		}

		void Hud::close()
		{
			level_text->isActive = false;
			money_text->isActive = false;
			wave_text->isActive = false;
			score_text->isActive = false;
			help_tower_text->isActive = false;
			count_down_text->isActive = false;
			pause_btn->isActive = false;
			retry_btn->isActive = false;
			up_speed_btn->isActive = false;
			stone_tower_btn->isActive = false;
			freeze_tower_btn->isActive = false;
			explosiv_tower_btn->isActive = false;
		}

		void Hud::set_level_text(const std::string& text)
		{
			level_text->set_text(text);
		}

		void Hud::set_money_text(const std::string& text)
		{
			money_text->set_text(truncate(text, text.find_first_of(".")+3) + " $");
		}

		void Hud::set_wave_text(const std::string& text)
		{
			wave_text->set_text(Constants::Config::wave_number_text + " " + text);
		}

		void Hud::set_score_text(const std::string& text)
		{
			score_text->set_text(text);
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

		void Hud::on_click_stone()
		{
			// todo: the best would be to handle that with btn desativated state.
			if (!Managers::Player::can_buy_tower(TowerId::StoneTower))
				return;

			on_start_placing_tower();
			Managers::Player::create_phantom_tower(TowerId::StoneTower);
		}

		void Hud::on_click_freeze()
		{
			if (!Managers::Player::can_buy_tower(TowerId::FreezeTower))
				return;

			on_start_placing_tower();
			Managers::Player::create_phantom_tower(TowerId::FreezeTower);
		}

		void Hud::on_click_explosiv()
		{
			if (!Managers::Player::can_buy_tower(TowerId::ExplosivTower))
				return;

			on_start_placing_tower();
			Managers::Player::create_phantom_tower(TowerId::ExplosivTower);
		}

		void Hud::on_start_placing_tower()
		{
			pause_btn->isActive = false;
			retry_btn->isActive = false;
			up_speed_btn->isActive = false;
			stone_tower_btn->isActive = false;
			freeze_tower_btn->isActive = false;
			explosiv_tower_btn->isActive = false;
			help_tower_text->isActive = true;
			// keep countdown
		}

		void Hud::on_tower_placed()
		{
			pause_btn->isActive = true;
			retry_btn->isActive = true;
			up_speed_btn->isActive = true;
			stone_tower_btn->isActive = true;
			freeze_tower_btn->isActive = true;
			explosiv_tower_btn->isActive = true;
			help_tower_text->isActive = false;
		}
		
		void Hud::start_count_down(const unsigned int& seconds)
		{
			count_down_active = true;
			preparation_time_remaining = seconds;
			count_down_text->isActive = true;
			set_count_dow_text(preparation_time_remaining);
			count_down_time_out_id = Utils::Timer::set_time_out(
				Sharp::EventHandler::Bind(&Hud::count_down),
				1.f
			);
		}

		void Hud::count_down()
		{
			count_down_time_out_id = 0;
			preparation_time_remaining--;
			set_count_dow_text(preparation_time_remaining);
			if (preparation_time_remaining != 0)
			{
				count_down_time_out_id = Utils::Timer::set_time_out(
					Sharp::EventHandler::Bind(&Hud::count_down),
					1.f
				);
			} 
			else
			{
				count_down_active = false;
				count_down_text->isActive = false;
			}
		}

		void Hud::set_count_dow_text(const unsigned int& seconds)
		{
			count_down_text->set_text(std::to_string(preparation_time_remaining));
			const float factor_alpha = static_cast<float>(std::min(4u, preparation_time_remaining))/4.f;
			count_down_text->set_text_color(sf::Color(255,255,255, static_cast<sf::Uint8>(255 * factor_alpha)));
		}
	}
}
