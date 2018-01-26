#pragma once
#include "Tile.hpp"
#ifndef SPAWN_HPP
#define SPAWN_HPP

namespace TowerDefense
{
	namespace Game
	{
		class Spawn : public Tile
		{
		public:
			Spawn(const sf::Vector2u map_pos);
		};
	}
}
#endif
