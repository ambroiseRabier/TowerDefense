#include "stdafx.h"
#include "Collider.hpp"
#include "Debug.hpp"
#include "../../Circle.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		Collider::Collider(Tag newTag)
		{
		}

		Collider::Collider(const sf::FloatRect newRect, Tag newTag) : tag(newTag), type(Type::Rect), rect(newRect)
		{
		}

		Collider::Collider(const sf::Sprite& newSprite, Tag newTag, Type newType) : tag(newTag), type(newType), sprite(&newSprite)
		{
			Debug::assert_m(
				type == Type::SpriteRect 
			 || type == Type::SpriteCircle 
			 || type == Type::SpritePixelPerfect,
				"Collider: the type must be SpriteRect or SpriteCircle or SpritePixelPerfect."
			);
		}

		Collider::Collider(const sf::Vector2f newDot, Tag newTag) : tag(newTag), type(Type::Dot), dot(newDot)
		{
		}

		Collider::Collider(const Circle newCircle, Tag newTag) : tag(newTag), type(Type::Circle), circle(newCircle)
		{
		}

		Collider::Collider(sf::Vector2f circle_center, float circle_radius, Tag newTag)
						: tag(newTag), type(Type::Circle), circle(Circle(circle_radius, circle_center))
		{
		}

		Collider::~Collider()
		{
			if (sprite) sprite = nullptr; // useless ? (don't delete it, you don't have authority)
		}

		Collider::Type Collider::get_type() const
		{	
			return type;
		}

		const sf::Vector2f& Collider::get_dot() const
		{
			Debug::assert_m(
				type == Type::Dot, 
				"Collider: collider is not of type Dot. But you are trying to access it."
			);
			return dot;
		}

		const sf::FloatRect& Collider::get_rect() const
		{
			Debug::assert_m(
				type == Type::Rect, 
				"Collider: collider is not of type Rect. But you are trying to access it."
			);
			return rect;
		}

		const Circle& Collider::get_circle() const
		{
			Debug::assert_m(
				type == Type::Circle, 
				"Collider: collider is not of type Circle. But you are trying to access it."
			);
			return circle;
		}

		const sf::Sprite& Collider::get_sprite() const
		{
			Debug::assert_m(
				type == Type::SpriteRect 
			 || type == Type::SpriteCircle 
			 || type == Type::SpritePixelPerfect,
				"Collider: collider is neither of type SpriteRect or SpriteCircle or SpritePixelPerfect. But you are trying to access it."
			);
			return *sprite;
		}

		void Collider::set_dot(sf::Vector2f new_dot)
		{
			Debug::assert_m(
				type == Type::Dot, 
				"Collider: collider is not of type Dot. But you are trying to access it."
			);
			dot = new_dot;
		}

		void Collider::set_rect(sf::FloatRect new_rect)
		{
			Debug::assert_m(
				type == Type::Rect, 
				"Collider: collider is not of type Rect. But you are trying to access it."
			);
			rect = new_rect;
		}

		void Collider::set_circle(Circle new_circle)
		{
			Debug::assert_m(
				type == Type::Circle, 
				"Collider: collider is not of type Circle. But you are trying to access it."
			);
			circle = new_circle;
		}

		void Collider::set_circle(const sf::Vector2f& position, const float& radius)
		{
			Debug::assert_m(
				type == Type::Circle, 
				"Collider: collider is not of type Circle. But you are trying to access it."
			);
			circle.position = position;
			circle.radius = radius;
		}
	}

}

