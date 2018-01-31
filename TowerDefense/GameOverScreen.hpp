#pragma once
#ifndef GAME_OVER_SCREEN_HPP
#define GAME_OVER_SCREEN_HPP
#include "GameObjects/BaseButton.hpp"
#include "BaseText.hpp"
#include <memory>

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
			static void on_click_retry();
			static void on_click_menu_return();
		};
	}
}
#endif
