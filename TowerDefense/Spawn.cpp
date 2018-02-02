#include "stdafx.h"
#include "Spawn.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Spawn::Spawn(const sf::Vector2u map_pos) : Tile(Spawn_Other, map_pos)
		{
		}
	}
}
