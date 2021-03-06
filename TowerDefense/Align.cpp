#include "stdafx.h"
#include "Align.hpp"
#include "Config.hpp"
#include "GameEngine/DisplayManager.hpp"

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
				DisplayManager::get_height() - offset
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
				DisplayManager::get_width() - offset,
				transformable.getPosition().y
			);
		}

		void Align::center(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				// dividing int by int ?
				DisplayManager::get_width()/2 + offset.x,
				DisplayManager::get_height()/2 + offset.y
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
				DisplayManager::get_width() - offset.x,
				offset.y
			);
		}

		void Align::bottom_left(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				offset.x,
				DisplayManager::get_height() - offset.y
			);
		}

		void Align::bottom_right(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				DisplayManager::get_width() - offset.x,
				DisplayManager::get_height() - offset.y
			);
		}

		void Align::top_center(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				// dividing int by int ?
				DisplayManager::get_width()/2 + offset.x,
				offset.y
			);
		}

		void Align::bottom_center(sf::Transformable& transformable, const sf::Vector2f& offset)
		{
			transformable.setPosition(
				// dividing int by int ?
				DisplayManager::get_width()/2 + offset.x,
				DisplayManager::get_height() - offset.y
			);
		}
		//todo surcharge avec 3 param au lieu de vec2

		// end region
	}
}
