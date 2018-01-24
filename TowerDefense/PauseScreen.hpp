#pragma once
#ifndef PAUSE_SCREEN_HPP
#define PAUSE_SCREEN_HPP
#include "GameObjects/BaseButton.hpp"

namespace TowerDefense
{
	namespace UI
	{
		class PauseScreen
		{
		public:
			static void init();
			static void destroy();
			static void open();
			static void close();
		private:
			static std::unique_ptr<BaseButton> resume_btn;
			static std::unique_ptr<BaseButton> menu_return_btn;
			static void on_click_resume();
			static void on_click_menu_return();
		};
	}
}
#endif
