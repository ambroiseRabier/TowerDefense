#pragma once
#ifndef BASE_BUTTON_HPP
#define BASE_BUTTON_HPP
#include "BaseGameObject.hpp"

namespace TowerDefense
{
	namespace UI
	{
		/**
		 * \brief 
		 * 
		 * Usage example:
		 * 	UI::BaseButton* base_button = new UI::BaseButton();
		 * base_button->get_transformable().setPosition(200,200);
		 * base_button->auto_start();
		 * base_button->destroy();
		 * delete base_button;
		 * base_button = nullptr;
		 */
		class BaseButton:public GameEngine::BaseGameObject
		{
		public:
			void destroy() override;
			void on_mouse_overlap() override;
			void on_mouse_click(bool left) override;
		protected:
			void init() override;
		};
	}
}
#endif

