#pragma once
#ifndef BASE_BUTTON_HPP
#define BASE_BUTTON_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "Utils/Event.h"
#include "../../Config.hpp"


namespace TowerDefense
{
	namespace UI
	{
		/**
		 * \brief 
		 * Class to display a simple button with custom text.
		 * For UI screens mostly.
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
			BaseButton();
			BaseButton(sf::Texture* pTexture, const unsigned int& new_z_index = Constants::ZIndex::ui_start);
			~BaseButton();
			void on_mouse_overlap() override;
			void on_mouse_overlap_front() override;
			void on_mouse_click(bool left) override;
			void on_mouse_click_front(bool left) override;
			void on_game_object_overlap(GameObject& game_object) override;
			void set_text(std::string new_text);
			std::string get_text();
			/**
			 * \brief Called on click.
			 */
			Sharp::Event<void> on_click;
			sf::Sprite& get_sprite() const;
		protected:
			sf::Sprite* sprite;
			sf::Text text;
			void init() override;
			void create_button(sf::Texture* pTexture);
			void update() override;
		};
	}
}
#endif

