#include "stdafx.h"
#include "BaseButton.hpp"
#include "Constants.hpp"
#include "Debug.hpp"

using namespace TowerDefense::GameEngine;

namespace TowerDefense
{
	namespace UI
	{
		void BaseButton::init()
		{
			BaseGameObject::init();
			// shared_ptr is removed when going out of scope.
			std::shared_ptr<sf::Sprite> my_sprite = std::make_shared<sf::Sprite>(*GlobalShared::default_ui_btn);
			//my_sprite->setPosition(0,0);
			//sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
			//sprite.setColor(sf::Color(255, 255, 255, 200));
			set_drawable(
				std::move(static_cast<std::shared_ptr<sf::Drawable>>(
					// cannot downcast or keep a reference of Sprite, unique pointer for a Sprite being
					// kept as Drawable is rather problematic.
					//std::make_unique<sf::Sprite>(*GlobalShared::default_ui_btn)
					my_sprite
				))
			);
			// since I used std::move, do not call my_sprite anymore !

			z_index = Constants::ZIndex::ui_start;
			collider = std::make_shared<Collider>(
				std::make_unique<sf::FloatRect>(sf::FloatRect(0,0,341,148)),
				Collider::Tag::UI
			);
			//collider->tag = Collider::Tag::UI;

		}

		void BaseButton::destroy()
		{
			BaseGameObject::destroy();
		}

		void BaseButton::on_mouse_overlap()
		{
			
		}

		void BaseButton::on_mouse_overlap_front()
		{

		}

		void BaseButton::on_mouse_click(bool left)
		{
			Debug::log("on_mouse_click " + left);
		}

		void BaseButton::on_mouse_click_front(bool left)
		{
			Debug::log("on_mouse_click_front " + left);
		}
	}
}
