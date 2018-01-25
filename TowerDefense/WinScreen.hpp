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
			static void close();
		private:
			static std::unique_ptr<BaseButton> menu_return_btn;
			static void on_click_menu_return();
		};
	}
}
#endif
