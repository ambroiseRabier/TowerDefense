#include "stdafx.h"
#include "CollisionTest.hpp"
#include "Debug.hpp"
#include "Collision.h"

namespace TowerDefense
{
	namespace GameEngine
	{
		class Collider;
		bool CollisionTest::collide(const Collider& collider1, const Collider& collider2)
		{
			if (collider1.get_type() == Collider::Type::Rect 
				&& collider2.get_type() == Collider::Type::Rect)
				return rect_rect(collider1.get_rect(), collider2.get_rect());
			if (collider1.get_type() == Collider::Type::Rect 
				&& collider2.get_type() == Collider::Type::Dot)
				return rect_dot(collider1.get_rect(), collider2.get_dot());
			if (collider1.get_type() == Collider::Type::Dot 
				&& collider2.get_type() == Collider::Type::Rect)
				return rect_dot(collider2.get_rect(), collider1.get_dot());
			if (collider1.get_type() == Collider::Type::SpriteRect
				&& collider2.get_type() == Collider::Type::SpriteRect)
				return Collision::BoundingBoxTest(collider1.get_sprite(), collider2.get_sprite());
			if (collider1.get_type() == Collider::Type::SpriteCircle
				&& collider2.get_type() == Collider::Type::SpriteCircle)
				return Collision::CircleTest(collider1.get_sprite(), collider2.get_sprite());
			if (collider1.get_type() == Collider::Type::SpritePixelPerfect
				&& collider2.get_type() == Collider::Type::SpritePixelPerfect)
				return Collision::PixelPerfectTest(collider1.get_sprite(), collider2.get_sprite());
			

			Debug::warn("CollisionTest: No available collision test for this collider type. Add one. Or it will always be false.");
			return false;
		}

		bool CollisionTest::rect_dot(const sf::FloatRect& rect, const sf::Vector2f& dot)
		{
			return rect.contains(dot);
		}

		bool CollisionTest::rect_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
		{// todo: use axis separation theorem. (rotation)
			const float right1 =  rect1.left + rect1.width;
			const float right2 =  rect2.left + rect2.width;
			const float bottom1 =  rect1.top + rect1.height;
			const float bottom2 =  rect2.top + rect2.height;
			return !(rect1.left < right2 
				&& right1 > rect2.left 
				&& rect1.top > bottom2 
				&& bottom1 < rect2.top);
		}
	}
}
