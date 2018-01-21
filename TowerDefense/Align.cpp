#include "stdafx.h"
#include "Align.hpp"
#include "Constants.hpp"

using namespace TowerDefense::Constants::Config;
namespace TowerDefense
{
	namespace UI
	{
		//might use window.GetSize() later...

		void Align::top(sf::Transformable& transformable, const float& offset)
		{
			transformable.setPosition(
				transformable.getPosition().x,
				offset
			);
		}

		void Align::bottom(sf::Transformable& transformable, const float& offset)
		{
			transformable.setPosition(
				transformable.getPosition().x,
				window_height - offset
			);
		}

		void Align::right(sf::Transformable& transformable, const float& offset)
		{
			transformable.setPosition(
				offset,
				transformable.getPosition().y
			);
		}

		void Align::left(sf::Transformable& transformable, const float& offset)
		{
			transformable.setPosition(
				window_width - offset,
				transformable.getPosition().y
			);
		}

		void Align::center(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				// dividing int by int ?
				window_width/2 + offset.x,
				window_height/2 + offset.y
			);
		}
	}
}
