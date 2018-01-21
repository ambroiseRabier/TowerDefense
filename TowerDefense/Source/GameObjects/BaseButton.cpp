#include "stdafx.h"
#include "BaseButton.hpp"
#include "Constants.hpp"
#include "../../CastUtils.hpp"
#include "GameEngine/Debug.hpp"

using namespace TowerDefense::GameEngine;

namespace TowerDefense
{
	namespace UI
	{
		BaseButton::BaseButton()
		{
			std::unique_ptr<sf::Sprite> my_sprite = std::make_unique<sf::Sprite>(*GlobalShared::default_ui_btn);
			// I prefer avoiding downcast of the drawable into sprite
			// sprite get a pointer, that will be null after destroy() method being called.
			// It do not own the sprite memory.
			sprite = my_sprite.get();
			set_drawable(
				// std::move(static_cast<std::unique_ptr<sf::Drawable>>( not ok
				// std::move(static_cast<std::shared_ptr<sf::Drawable>>( ok
				// weird
				std::move(static_cast_ptr<sf::Drawable>(
					my_sprite
				))
			);
			// since I used std::move, do not call my_sprite anymore ! 
			// But I can still use drawable field. or sprite field.
			//sprite->setPosition(0,0);
			//sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
			//sprite.setColor(sf::Color(255, 255, 255, 200));
			collider = std::make_shared<Collider>(
				std::make_unique<sf::FloatRect>(sf::FloatRect(0,0,137,60)),
				Collider::Tag::UI
			);
			//collider->tag = Collider::Tag::UI;
			z_index = Constants::ZIndex::ui_start;
		}

		//keep this or only parent object will have destroy() called
		BaseButton::~BaseButton()
		{
			destroy();
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

		void BaseButton::destroy()
		{
			// make sure it is called one time only if someone inherit from you.
			if (!base_btn_destroyed)
			{
				base_btn_destroyed = true;
				//your code here
				BaseGameObject::destroy();
			}
		}

		void BaseButton::unListenToEvents()
		{
			//your code here
			BaseGameObject::unListenToEvents();
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
			//Debug::log("on_mouse_click_front " + left);
			on_click();
		}

		void BaseButton::on_game_object_overlap(GameObject& game_object)
		{
			//Debug::log("on_game_object_overlap base_btn");
		}

		void BaseButton::set_text(std::string new_text)
		{
			//todo
		}

		std::string BaseButton::get_text()
		{
			return "todo";
		}
	}
}
