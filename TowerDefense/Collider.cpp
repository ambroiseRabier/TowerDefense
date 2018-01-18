#include "stdafx.h"
#include "Collider.hpp"
#include "Debug.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		Collider::Collider()
		{
			type = Type::None;
			Debug::warn("Collider: you should not call default constructor, there is no way to set collider elsewhere then constructor.");
		}

		Collider::Collider(std::unique_ptr<sf::FloatRect> newRect, Tag newTag) : tag(newTag), rect(std::move(newRect))
		{
			type = Type::Rect;
		}

		Collider::~Collider()
		{
			if (rect.get()) rect.reset(nullptr);
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

