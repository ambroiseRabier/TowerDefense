#include "stdafx.h"
#include "CollisionTest.hpp"
#include "Debug.hpp"
#include "Utils/Collision.h"
#include "../../Mathf.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
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

			/*if (collider1.get_type() == Collider::Type::Circle 
				&& collider2.get_type() == Collider::Type::Rect)
				return circle_rect(collider1.get_circle(), collider2.get_rect());
			if (collider1.get_type() == Collider::Type::Rect 
				&& collider2.get_type() == Collider::Type::Circle)
				return circle_rect(collider2.get_circle(), collider1.get_rect());*/

			if (collider1.get_type() == Collider::Type::SpriteRect
				&& collider2.get_type() == Collider::Type::SpriteRect)
				return bounding_box_test(collider1.get_sprite(), collider2.get_sprite());
			if (collider1.get_type() == Collider::Type::SpriteCircle
				&& collider2.get_type() == Collider::Type::SpriteCircle)
				return circle_test(collider1.get_sprite(), collider2.get_sprite());
			if (collider1.get_type() == Collider::Type::SpritePixelPerfect
				&& collider2.get_type() == Collider::Type::SpritePixelPerfect)
				return pixel_perfect_test(collider1.get_sprite(), collider2.get_sprite());
			
			Debug::warn(
				"Physics: Collider for mouse type not supported. Add support for: " 
				//+ Collider::Type_to_string(collider1->get_type()) + " and "
				//+ Collider::Type_to_string(collider2->get_type())
			);
			Debug::warn("CollisionTest: No available collision test for this collider type. Add one. Or it will always be false.");
			return false;
		}

		bool CollisionTest::rect_dot(const sf::FloatRect& rect, const sf::Vector2f& dot)
		{
			return rect.contains(dot);
		}

		bool CollisionTest::rect_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
		{// todo: use axis separation theorem. (rotation)
			return rect1.intersects(rect2);
			/*const float right1 =  rect1.left + rect1.width;
			const float right2 =  rect2.left + rect2.width;
			const float bottom1 =  rect1.top + rect1.height;
			const float bottom2 =  rect2.top + rect2.height;
			return !(rect1.left < right2 
				&& right1 > rect2.left 
				&& rect1.top > bottom2 
				&& bottom1 < rect2.top);*/
		}

		// https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection#402010
		// with no XOR on float.... : http://www.migapro.com/circle-and-rotated-rectangle-collision-detection/
		/*bool CollisionTest::circle_rect(const Circle& circle, const sf::FloatRect& rect, const float& angle_radian)
		{ 
			const sf::Vector2f rectCenter(
				rect.left + rect.width/2.f,
				rect.top + rect.height/2.f // on the link they seem to do it that way... but I would use - rect.height/2.f
			);
			// Rotate circle's center point back
			const double unrotatedCircleX = cos(angle_radian) * (circle.position.x - rectCenter.x) - 
					sin(angle_radian) * (circle.position.y - rectCenter.y) + rectCenter.x;
			const double unrotatedCircleY = sin(angle_radian) * (circle.position.x - rectCenter.x) + 
					cos(angle_radian) * (circle.position.y - rectCenter.y) + rectCenter.y;
 
			// Closest point in the rectangle to the center of circle rotated backwards(unrotated)
			double closestX, closestY;
 
			// Find the unrotated closest x point from center of unrotated circle
			if (unrotatedCircleX  < rect.left)
				closestX = rect.left;
			else if (unrotatedCircleX  > rect.left + rect.width)
				closestX = rect.left + rect.width;
			else
				closestX = unrotatedCircleX ;
 
			// Find the unrotated closest y point from center of unrotated circle
			if (unrotatedCircleY < rect.top)
				closestY = rect.top;
			else if (unrotatedCircleY > rect.top + rect.height)
				closestY = rect.top + rect.height;
			else
				closestY = unrotatedCircleY;
 
			const double distance = Utils::findDistance(unrotatedCircleX , unrotatedCircleY, closestX, closestY);
			return distance < circle.radius;
		}*/

		bool CollisionTest::pixel_perfect_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2, sf::Uint8 alpha_limit)
		{
			return Collision::PixelPerfectTest(sprite1, sprite2, alpha_limit);
		}

		bool CollisionTest::create_texture_and_bitmask(sf::Texture& load_into, const std::string& file_name)
		{
			return Collision::CreateTextureAndBitmask(load_into, file_name);
		}

		bool CollisionTest::circle_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
		{
			return Collision::CircleTest(sprite1, sprite2);
		}

		bool CollisionTest::bounding_box_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
		{
			return Collision::BoundingBoxTest(sprite1, sprite2);
		}



	}
}
