#pragma once
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP
#include "GameObjects/BaseButton.hpp"

namespace TowerDefense
{
	namespace UI
	{
		class MenuScreen
		{
		public:
			static void init();
			static void open();
			static void close();
		private:
			static std::unique_ptr<BaseButton> play_btn;
			static std::unique_ptr<BaseButton> quit_btn;
			static void on_click_play();
			static void on_click_quit();
		};
	}
}
#endif
