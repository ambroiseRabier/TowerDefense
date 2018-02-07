#pragma once
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP
#include "GameObjects/BaseButton.hpp"
#include "BaseText.hpp"
#include <memory>

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
			static std::unique_ptr<GameObject> background;
			static std::unique_ptr<BaseButton> play_btn;
			static std::unique_ptr<BaseButton> quit_btn;
			static std::unique_ptr<BaseText> title_text;
			static std::unique_ptr<BaseText> credits_text;
			static void on_click_play();
			static void on_click_quit();
		};
	}
}
#endif
