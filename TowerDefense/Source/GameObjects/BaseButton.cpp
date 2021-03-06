#include "stdafx.h"
#include "BaseButton.hpp"
#include "GameEngine/Debug.hpp"
#include "../../GlobalShared.hpp"
#include "../../Config.hpp"
#include "../../Timer.hpp"
#include "../../UIAssets.hpp"
#include "../../SoundManager.hpp"
#include "../../SoundsAssets.hpp"

using namespace TowerDefense::GameEngine;

namespace TowerDefense
{
	namespace UI
	{
		BaseButton::BaseButton()
		{
			create_button(GlobalShared::get_texture(Constants::UIAssets::default_ui_btn));
		}

		BaseButton::BaseButton(sf::Texture* pTexture, const unsigned int& new_z_index)
		{
			create_button(pTexture);
			// not member of, so have to initialize here.
			z_index = new_z_index;
		}

		BaseButton::BaseButton(sf::Texture* pTexture, const std::string& text, const sf::Vector2f& offset_text,
			const unsigned int& new_z_index)
		{
			create_button(pTexture);
			// not member of, so have to initialize here.
			z_index = new_z_index;
			create_text(text, offset_text);
		}

		BaseButton::~BaseButton()
		{
		}

		void BaseButton::create_button(sf::Texture* pTexture) {
			std::shared_ptr<sf::Sprite> my_sprite = std::make_shared<sf::Sprite>(*pTexture);
			// I prefer avoiding downcast of the drawable into sprite
			// sprite get a pointer, that will be null after destroy() method being called.
			// It do not own the sprite memory.
			sprite = my_sprite.get();
			set_drawable(
				// std::move(static_cast<std::unique_ptr<sf::Drawable>>( not ok
				// std::move(static_cast<std::shared_ptr<sf::Drawable>>( ok
				// weird
				std::move(my_sprite)
			);
			// since I used std::move, do not call my_sprite anymore ! 
			// But I can still use drawable field. or sprite field.
			//sprite->setPosition(0,0);
			//sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
			//sprite.setColor(sf::Color(255, 255, 255, 200));
			// take collision box of sprite
			collider = std::make_shared<Collider>(
				sprite->getLocalBounds(),
				Collider::Tag::UI
			);
			//collider->tag = Collider::Tag::UI;
			z_index = Constants::ZIndex::ui;
		}

		void BaseButton::create_text(const std::string& text, const sf::Vector2f& offset_text)
		{
			std::shared_ptr<sf::Text> my_text = std::make_shared<sf::Text>();
			my_text->setString(text);
			my_text->setPosition(offset_text);
			my_text->setOutlineColor(sf::Color::White);
			my_text->setFont(*GlobalShared::default_font);
			my_text->setCharacterSize(16); // hard coded for hud tower btn.
			add_drawable(std::move(my_text));
		}

		void BaseButton::init()
		{
			BaseGameObject::init();
		}

		void BaseButton::update()
		{
			//BaseGameObject::update(); there is nothing to call, so we can ignore base call here.
			// your code here
		}

		void BaseButton::on_mouse_overlap()
		{
			//Debug::log("on_mouse_overlap");
		}

		void BaseButton::on_mouse_overlap_front()
		{
			//Debug::log("on_mouse_overlap_front");
		}

		void BaseButton::on_mouse_click(bool left)
		{
			//Debug::log("on_mouse_click " + left);
		}

		void BaseButton::on_mouse_click_front(bool left)
		{
			SoundManager::play_one_shoot(Constants::SoundsAssets::btn_click_ui);
			on_click();
		}

		void BaseButton::on_game_object_overlap(GameObject& game_object)
		{
			//Debug::log("on_game_object_overlap base_btn");
		}

		void BaseButton::set_text(std::string new_text)
		{

		}

		std::string BaseButton::get_text()
		{
			return "text";
		}

		sf::Sprite& BaseButton::get_sprite() const
		{
			Debug::assert_m(sprite, "BaseButton: Sprite being nullptr is unexpected.");
			return *sprite;
		}

	}
}
