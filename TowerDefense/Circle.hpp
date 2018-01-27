#pragma once
#ifndef CIRCLE_HPP
#define CIRCLE_HPP
namespace TowerDefense
{
	namespace GameEngine
	{
		class Circle
		{
		public:
			friend bool operator==(const Circle& lhs, const Circle& rhs)
			{
				return lhs.radius == rhs.radius
					&& lhs.position == rhs.position;
			}

			friend bool operator!=(const Circle& lhs, const Circle& rhs)
			{
				return !(lhs == rhs);
			}

			Circle(float radius = 1.f, const sf::Vector2f& position = sf::Vector2f(0,0));
			~Circle();
			float radius;
			sf::Vector2f position;
		};
	}
}
#endif
