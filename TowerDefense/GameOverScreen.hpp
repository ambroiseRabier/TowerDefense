#pragma once
#ifndef GAME_OVER_SCREEN_HPP
#define GAME_OVER_SCREEN_HPP
#include "GameObjects/BaseButton.hpp"
#include "BaseText.hpp"

namespace TowerDefense
{
	namespace UI
	{
		class GameOverScreen
		{
		public:
			static void init();
			static void open();
			static void close();
		private:
			static void destroy();
			static std::unique_ptr<BaseButton> retry_btn;
			static std::unique_ptr<BaseButton> menu_return_btn;
			static std::unique_ptr<BaseText> title_text;
			static std::unique_ptr<BaseText> score_text;
			static void on_click_retry();
			static void on_click_menu_return();
			static void set_score_text(const unsigned& value);
		};
	}
}
#endif
