#include "BaseButton.hpp"
#include "stdafx.h"
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
			Debug::log("base btn initVar");
			set_drawable(
				static_cast<std::unique_ptr<sf::Drawable>>(
					std::make_unique<sf::Sprite>(*GlobalShared::default_ui_btn)
				)
			);
			z_index = 4;
			/*
			// Declare and load a texture
			sf::Texture texture;
			texture.loadFromFile("Assets/orange_btn.jpg");
			// Create a sprite
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
			sprite.setColor(sf::Color(255, 255, 255, 200));
			sprite.setPosition(100, 25);
			// Draw it
			window.draw(sprite);
			*/
		}

		void BaseButton::onDestroy()
		{
			Debug::log("bgm onDestroy");
		}
	}
}
