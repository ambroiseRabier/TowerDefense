#pragma once
#ifndef COLLISION_TEST_HPP
#define COLLISION_TEST_HPP
#include "Collider.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		/**
		 * \brief 
		 * Contain collisions methods used by Physics.
		 */
		class CollisionTest
		{
		public:
			static bool collide(const Collider& collider1, const Collider& collider2);
			static bool rect_dot(const sf::FloatRect& rect, const sf::Vector2f& dot);
			static bool rect_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
			static bool pixel_perfect_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2, sf::Uint8 alpha_limit = 0);
			static bool create_texture_and_bitmask(sf::Texture& load_into, const std::string& file_name);
			static bool circle_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
			static bool bounding_box_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
		};
	}
}
#endif

