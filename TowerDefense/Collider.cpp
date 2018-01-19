#include "stdafx.h"
#include "Collider.hpp"
#include "Debug.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		Collider::Collider(std::unique_ptr<sf::FloatRect> newRect, Tag newTag) : tag(newTag), rect(std::move(newRect))
		{
			type = Type::Rect;
		}

		Collider::Collider(const sf::Sprite& newSprite, Tag newTag, Type newType) : tag(newTag), sprite(&newSprite), type(newType)
		{
			Debug::assert_m(
				type == Type::SpriteRect 
			 || type == Type::SpriteCircle 
			 || type == Type::SpritePixelPerfect,
				"Collider: the type must be SpriteRect or SpriteCircle or SpritePixelPerfect."
			);
		}

		Collider::Collider(std::unique_ptr<sf::Vector2f> newDot, Tag newTag) : tag(newTag), dot(std::move(newDot))
		{
			type = Type::Dot;
		}

		Collider::~Collider()
		{
			if (rect.get()) rect.reset(nullptr);
			if (dot.get()) dot.reset(nullptr);
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
			return *dot;
		}

		const sf::FloatRect& Collider::get_rect() const
		{
			Debug::assert_m(
				type == Type::Rect, 
				"Collider: collider is not of type Rect. But you are trying to access it."
			);
			return *rect;
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
	}

}

