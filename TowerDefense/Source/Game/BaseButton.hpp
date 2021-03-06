#pragma once
#ifndef BASE_BUTTON_HPP
#define BASE_BUTTON_HPP
#include "GameEngine/BaseGameObject.hpp"

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
			void on_mouse_overlap_front() override;
			void on_mouse_click(bool left) override;
			void on_mouse_click_front(bool left) override;
			void on_game_object_overlap(GameObject& game_object) override;
		protected:
			void init() override;
		};
	}
}
#endif

