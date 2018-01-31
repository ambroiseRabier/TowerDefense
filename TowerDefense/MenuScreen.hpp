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
			/**
			 * \brief Should be called by main. 
			 * Destroy btn cannot be destroyed on it's own callback.
			 */
			static void destroy_quit_btn();
		private:
			static void destroy();
			static std::unique_ptr<BaseButton> play_btn;
			static std::unique_ptr<BaseButton> quit_btn;
			static void on_click_play();
			static void on_click_quit();
		};
	}
}
#endif
