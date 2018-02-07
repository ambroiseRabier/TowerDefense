#include "stdafx.h"
#include "CollisionTest.hpp"
#include "Debug.hpp"
#include "Utils/Collision.h"
#include "../../Mathf.hpp"
#include "GameObject.hpp"

using namespace sf;
namespace TowerDefense
{
	namespace GameEngine
	{
		
		bool CollisionTest::collide(const Collider& c1, const Collider& c2,
									const Transformable& t1, const Transformable& t2)
		{
			// rect rect
			if (c1.get_type() == Collider::Type::Rect 
				&& c2.get_type() == Collider::Type::Rect)
				return rect_rect(c1.get_rect(), c2.get_rect(), t1, t2);
			
			// rect dot
			if (c1.get_type() == Collider::Type::Rect 
				&& c2.get_type() == Collider::Type::Dot)
				return rect_dot(c1.get_rect(), c2.get_dot(), t1, t2);
			if (c1.get_type() == Collider::Type::Dot 
				&& c2.get_type() == Collider::Type::Rect)
				return rect_dot(c2.get_rect(), c1.get_dot(), t2, t1);

			// circle rect
			if (c1.get_type() == Collider::Type::Circle 
				&& c2.get_type() == Collider::Type::Rect)
				return circle_rect(c1.get_circle(), c2.get_rect(), t1, t2);
			if (c1.get_type() == Collider::Type::Rect 
				&& c2.get_type() == Collider::Type::Circle)
				return circle_rect(c2.get_circle(), c1.get_rect(), t2, t1);

			// circle dot
			if (c1.get_type() == Collider::Type::Circle 
				&& c2.get_type() == Collider::Type::Dot)
				return circle_dot(c1.get_circle(), c2.get_dot(), t1, t2);
			if (c1.get_type() == Collider::Type::Dot 
				&& c2.get_type() == Collider::Type::Circle)
				return circle_dot(c2.get_circle(), c1.get_dot(), t2, t1);
			
			// would be nice to change the enum to string for debu message.
			//Debug::warn(
				//"CollisionManager: Collider for mouse type not supported. Add support for: " 
				//+ Collider::Type_to_string(collider1->get_type()) + " and "
				//+ Collider::Type_to_string(collider2->get_type())
			//);
			Debug::warn("CollisionTest: No available collision test for this collider type. Add one. Or it will always be false.");
			return false;
		}

		bool CollisionTest::rect_dot(const FloatRect& rect, const Vector2f& dot,
			const Transformable& transformable1, const Transformable& transformable2)
		{
			// take in account only position of the transform
			// (I do not use transformRect function from Transform class because do weird stuff with rotation...)
			// maybe it's just rectangle shape that does weird ? 
			// rotation collision for rect-rect and rect-dot and rect-circle should be not too hard to implement
			FloatRect rect_global(rect);
			rect_global.left += transformable1.getPosition().x;
			rect_global.top += transformable1.getPosition().y;

			// take in account scale,rotation,position
			const Vector2f dot_global(transformable2.getTransform().transformPoint(dot));

			return rect_dot(rect_global, dot_global);
		}

		bool CollisionTest::rect_rect(const FloatRect& rect1, const FloatRect& rect2,
			const Transformable& transformable1, const Transformable& transformable2)
		{
			// position
			FloatRect rect_global_1(rect1);
			rect_global_1.left += transformable1.getPosition().x;
			rect_global_1.top += transformable1.getPosition().y;

			// position
			FloatRect rect_global_2(rect2);
			rect_global_2.left += transformable2.getPosition().x;
			rect_global_2.top += transformable2.getPosition().y;

			return rect_rect(rect_global_1, rect_global_2);
		}

		bool CollisionTest::circle_rect(const Circle& circle, const FloatRect& rect,
			const Transformable& transformable1, const Transformable& transformable2)
		{
			// position, rotation, not scale
			const Circle circle_global(circle.radius, transformable1.getTransform().transformPoint(circle.position));

			// position
			FloatRect rect_global(rect);
			rect_global.left += transformable2.getPosition().x;
			rect_global.top += transformable2.getPosition().y;

			// don't be fooled !
			// rotation parameter is for rotation from center of rectangle, not from transform !
			// until you sovle that don't use another rotation then 0.f
			return circle_rect(circle_global, rect_global, 0.f/*, transformable2.getRotation()*/);
		}

		bool CollisionTest::circle_dot(const Circle& circle, const Vector2f& dot,
			const Transformable& transformable1, const Transformable& transformable2)
		{
			// position, rotation, not scale
			const Circle circle_global(circle.radius, transformable1.getTransform().transformPoint(circle.position));

			// position roptation, scale
			const Vector2f dot_global(transformable2.getTransform().transformPoint(dot));

			return circle_dot(circle_global, dot_global);
		}


		// #######################################################
		// ################## IF SAME TRANSFORM ##################
		// #######################################################

		bool CollisionTest::collide_local(const Collider& c1, const Collider& c2)
		{
			// rect rect
			if (c1.get_type() == Collider::Type::Rect 
				&& c2.get_type() == Collider::Type::Rect)
				return rect_rect(c1.get_rect(), c2.get_rect());
			
			// rect dot
			if (c1.get_type() == Collider::Type::Rect 
				&& c2.get_type() == Collider::Type::Dot)
				return rect_dot(c1.get_rect(), c2.get_dot());
			if (c1.get_type() == Collider::Type::Dot 
				&& c2.get_type() == Collider::Type::Rect)
				return rect_dot(c2.get_rect(), c1.get_dot());

			// circle rect
			if (c1.get_type() == Collider::Type::Circle 
				&& c2.get_type() == Collider::Type::Rect)
				return circle_rect(c1.get_circle(), c2.get_rect(), 0.f);
			if (c1.get_type() == Collider::Type::Rect 
				&& c2.get_type() == Collider::Type::Circle)
				return circle_rect(c2.get_circle(), c1.get_rect(), 0.f);

			// circle dot
			if (c1.get_type() == Collider::Type::Circle 
				&& c2.get_type() == Collider::Type::Dot)
				return circle_dot(c1.get_circle(), c2.get_dot());
			if (c1.get_type() == Collider::Type::Dot 
				&& c2.get_type() == Collider::Type::Circle)
				return circle_dot(c2.get_circle(), c1.get_dot());

			// others
			if (c1.get_type() == Collider::Type::SpriteRect
				&& c2.get_type() == Collider::Type::SpriteRect)
				return bounding_box_test(c1.get_sprite(), c2.get_sprite());
			if (c1.get_type() == Collider::Type::SpriteCircle
				&& c2.get_type() == Collider::Type::SpriteCircle)
				return circle_test(c1.get_sprite(), c2.get_sprite());
			if (c1.get_type() == Collider::Type::SpritePixelPerfect
				&& c2.get_type() == Collider::Type::SpritePixelPerfect)
				return pixel_perfect_test(c1.get_sprite(), c2.get_sprite());
			
			Debug::warn("CollisionTest: No available LOCAL collision test for this collider type. Add one. Or it will always be false.");
			return false;
		}


		bool CollisionTest::rect_dot(const FloatRect& rect, const Vector2f& dot)
		{
			return rect.contains(dot);
		}

		bool CollisionTest::rect_rect(const FloatRect& rect1, const FloatRect& rect2)
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

		
		bool CollisionTest::circle_border_rect(const Circle& circle, const FloatRect& rect)
		{
			const Vector2f rect_center(
				rect.left + rect.width/2.f,
				rect.top + rect.height/2.f
			);

			const Vector2f dir_to_rec = Utils::normalize(rect_center - circle.position);
			// don't use fixed radius but distance between circle and rect clamped for circle_rect collision.
			const Vector2f closest_point = dir_to_rec * circle.radius + circle.position;
			return rect_dot(rect, closest_point);
		}

		// https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection#402010
		// with no XOR on float.... : http://www.migapro.com/circle-and-rotated-rectangle-collision-detection/
		// should handle rect rotation too. Not tested... Rotation from it's center I think
		bool CollisionTest::circle_rect(const Circle& circle, const FloatRect& rect, const float& angle_radian)
		{ 
			const Vector2f rectCenter(
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
		}

		bool CollisionTest::circle_dot(const Circle& circle, const Vector2f& vector2)
		{
			return Utils::magnitude(circle.position - vector2) < circle.radius;
		}

		bool CollisionTest::pixel_perfect_test(const Sprite& sprite1, const Sprite& sprite2, Uint8 alpha_limit)
		{
			return Collision::PixelPerfectTest(sprite1, sprite2, alpha_limit);
		}

		bool CollisionTest::create_texture_and_bitmask(Texture& load_into, const std::string& file_name)
		{
			return Collision::CreateTextureAndBitmask(load_into, file_name);
		}

		bool CollisionTest::circle_test(const Sprite& sprite1, const Sprite& sprite2)
		{
			return Collision::CircleTest(sprite1, sprite2);
		}

		bool CollisionTest::bounding_box_test(const Sprite& sprite1, const Sprite& sprite2)
		{
			return Collision::BoundingBoxTest(sprite1, sprite2);
		}
	}
}
