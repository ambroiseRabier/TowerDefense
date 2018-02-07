#include "stdafx.h"
#include "Circle.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		Circle::Circle(float radius, const sf::Vector2f& position)
				: radius(radius),
				  position(position)
		{
		}

		Circle::~Circle()
		{
		}
	}
}
