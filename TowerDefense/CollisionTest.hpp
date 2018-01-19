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
		};
	}
}
#endif

