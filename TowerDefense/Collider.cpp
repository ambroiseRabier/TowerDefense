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

		Collider::Collider(std::unique_ptr<sf::Vector2f> newDot, Tag newTag) : tag(newTag), dot(std::move(newDot))
		{
			type = Type::Dot;
		}

		Collider::~Collider()
		{
			if (rect.get()) rect.reset(nullptr);
		}

		sf::Vector2f& Collider::get_dot() const
		{
			return *dot;
		}

		Collider::Type Collider::get_type() const
		{	
			return type;
		}

		sf::FloatRect& Collider::get_rect() const
		{
			return *rect;
		}
	}

}

