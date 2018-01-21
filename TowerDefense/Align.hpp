#pragma once
#ifndef ALIGN_HPP
#define ALIGN_HPP

namespace TowerDefense
{
	namespace UI
	{
		class Align
		{
		public:
			static void top(sf::Transformable& transformable, const float& offset=0.f);
			static void bottom(sf::Transformable& transformable, const float& offset=0.f);
			static void right(sf::Transformable& transformable, const float& offset=0.f);
			static void left(sf::Transformable& transformable, const float& offset=0.f);
			static void center(sf::Transformable& transformable, const sf::Vector2f& offset);
		};
	}
}
#endif
