#pragma once
#include "GameObjects/BaseButton.hpp"
#include "BaseText.hpp"

namespace TowerDefense
{
	namespace UI
	{
		class GameClearedScreen
		{
		public:
			static void init();
			static void open();
			static void close();
		private:
			static void destroy();
			static std::unique_ptr<BaseButton> menu_return_btn;
			static std::unique_ptr<BaseText> title_text;
			static void on_click_menu_return();
		};
	}
}
