#include "stdafx.h"
#include "Align.hpp"
#include "GlobalShared.hpp"
#include "Config.hpp"

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

		void Align::top_left(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				offset.x,
				offset.y
			);
		}

		void Align::top_right(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				window_width - offset.x,
				offset.y
			);
		}

		void Align::bottom_left(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				offset.x,
				window_height - offset.y
			);
		}

		void Align::bottom_right(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				window_width - offset.x,
				window_height - offset.y
			);
		}

		void Align::top_center(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				// dividing int by int ?
				window_width/2 + offset.x,
				offset.y
			);
		}

		void Align::bottom_center(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				// dividing int by int ?
				window_width/2 + offset.x,
				window_height - offset.y
			);
		}

		// region gameobject surcharge

		/*void Align::top(sf::Sprite& sprite, const float& offset)
		{
		}

		void Align::bottom(GameObject& game_object, const float& offset)
		{
		}

		void Align::top_right(sf::Sprite& sprite, const sf::Vector2f offset)
		{
			offset.x -= sprite.getGlobalBounds().left - sprite.getGlobalBounds().width
			top_right(
				,
			);
		}*/

		// end region
	}
}
