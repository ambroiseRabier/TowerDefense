#pragma once
#ifndef MENU_BACKGROUND_HPP
#define MENU_BACKGROUND_HPP
#include "GameEngine/BaseGameObject.hpp"


namespace TowerDefense
{
	namespace UI
	{
		class MenuBackground: public GameEngine::BaseGameObject
		{
		public:
			void on_mouse_overlap() override;
			void on_mouse_overlap_front() override;
			void on_mouse_click(bool left) override;
			void on_mouse_click_front(bool left) override;
		protected:
			void init() override;
		};
	}
}
#endif
