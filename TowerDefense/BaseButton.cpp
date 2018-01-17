#include "BaseButton.hpp"
#include "stdafx.h"
#include "Constants.hpp"

namespace TowerDefense
{
	namespace UI
	{

		void BaseButton::initVar()
		{
			set_drawable(
				static_cast<std::unique_ptr<sf::Drawable>>(
					std::make_unique<sf::Sprite>(*GlobalShared::default_ui_btn)
				)
			);
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
	}
}
