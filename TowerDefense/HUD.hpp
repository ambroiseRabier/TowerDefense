#pragma once
#ifndef HUD_HPP
#define HUD_HPP
#include "Screen.hpp"
#include "BaseText.hpp"
#include "GameObjects/BaseButton.hpp"

namespace TowerDefense
{
	namespace UI
	{
		/**
		 * \brief 
		 * Should handle loose and win screen.
		 */
		class Hud : Screen
		{
		public:
			static void init();
			static void open();
			static void close();
			static void set_level_text(const std::string& text);
			static void set_money_text(const std::string& text);
			static void set_wave_text(const std::string& text);
			static void set_score_text(const std::string& text);
			static void on_start_placing_tower();
			/**
			 * \brief Re-activate retry and pause btn after new tower has been placed.
			 */
			static void on_tower_placed();
			static void start_count_down(const unsigned int& seconds);
		private:
			static void destroy();
			static std::unique_ptr<BaseText> level_text;
			static std::unique_ptr<BaseText> money_text;
			static std::unique_ptr<BaseText> wave_text;
			static std::unique_ptr<BaseText> help_tower_text;
			static std::unique_ptr<BaseText> count_down_text;
			static std::unique_ptr<BaseText> score_text;
			static std::unique_ptr<BaseButton> pause_btn;
			static std::unique_ptr<BaseButton> retry_btn;

			/**
			 * \brief 
			 * Button to up speed of the game.
			 * should call GameManager to up speed by x value
			 */
			static std::unique_ptr<BaseButton> up_speed_btn;
			static std::unique_ptr<BaseButton> stone_tower_btn;
			static std::unique_ptr<BaseButton> freeze_tower_btn;
			static std::unique_ptr<BaseButton> explosiv_tower_btn;
			static unsigned int preparation_time_remaining;
			static unsigned int count_down_time_out_id;
			static bool count_down_active;
			static void on_click_up_speed();
			static void on_click_retry();
			static void on_click_pause();
			static void on_click_stone();
			static void on_click_freeze();
			static void on_click_explosiv();
			static void count_down();
			static void set_count_dow_text(const unsigned& seconds);
		};
	}
}
#endif
