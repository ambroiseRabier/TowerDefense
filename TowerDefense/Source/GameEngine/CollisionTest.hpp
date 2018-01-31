#pragma once
#ifndef COLLISION_TEST_HPP
#define COLLISION_TEST_HPP
#include "Collider.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		class GameObject;

		/**
		 * \brief 
		 * Contain collisions methods used by Physics.
		 * DO NOT TAKE TRANSFORM SCALE AND ROTATION IN ACCOUNT 
		 * Altough it might implement it partially in collision test, you should not rely on it and make sure there is no scale or rotation
		 * on your GameObject. Exception for dot that can take in account scale and rotation.
		 * collision box displayed for debug might not be correct if you have a scale or rotation. (exception for dots)
		 * ----
		 * ! IF YOU WANT TO HAVE A FULL WORKING COLLISION CLASS you better find a librairy that does it for you instead of recoding !
		 * ----
		 * All methods have not been tested too.
		 */
		class CollisionTest
		{
		public:

			/**
			 * \brief Collision taking in account ther parent transform, only take in account position for now.
			 * \param collider1 
			 * \param collider2 
			 * \param transformable_global_1 
			 * \param transformable_global_2 
			 * \return 
			 */
			static bool collide(const Collider& collider1, const Collider& collider2, 
								const sf::Transformable& transformable_global_1, const sf::Transformable& transformable_global_2);
			static bool rect_dot(const sf::FloatRect& rect, const sf::Vector2f& dot, const sf::Transformable& transformable1, const sf::Transformable& transformable2);
			static bool rect_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2, const sf::Transformable& transformable1, const sf::Transformable& transformable2);
			static bool circle_rect(const Circle& circle, const sf::FloatRect& rect, const sf::Transformable& transformable1, const sf::Transformable& transformable2);
			static bool circle_dot(const Circle& circle, const sf::Vector2f& dot, const sf::Transformable& transformable1, const sf::Transformable& transformable2);

			/**
			 * \brief Collision for collider in the SAME TRANSFORM.
			 * \param collider1 
			 * \param collider2 
			 * \return 
			 */
			static bool collide_local(const Collider& collider1, const Collider& collider2);   // NOLINT
			static bool rect_dot(const sf::FloatRect& rect, const sf::Vector2f& dot);
			static bool rect_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
			static bool circle_border_rect(const Circle& circle, const sf::FloatRect& rect);
			static bool circle_rect(const Circle& circle, const sf::FloatRect& rect, const float& angle_radian);
			static bool circle_dot(const Circle& circle, const sf::Vector2f& dot);
			static bool pixel_perfect_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2, sf::Uint8 alpha_limit = 0);
			static bool create_texture_and_bitmask(sf::Texture& load_into, const std::string& file_name);
			static bool circle_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
			static bool bounding_box_test(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
		};

	}
}
#endif

