#pragma once
#ifndef WIN_SCREEN_HPP
#define WIN_SCREEN_HPP
#include "GameObjects/BaseButton.hpp"

namespace TowerDefense
{
	namespace UI
	{
		class WinScreen
		{
		public:
			static void init();
			static void open();
			static void destroy();
			static void setScore(int pScore);
			static void close();
		private:
			static std::unique_ptr<BaseButton> menu_return_btn;
			static void on_click_menu_return();
			static void createText();
			static float score;
		};
	}
}
#endif
