#include "stdafx.h"
#include "Castle.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Castle::Castle(const sf::Vector2u map_pos) : Tile(GlobalShared::castle_others_texture, Castle_Other, map_pos)
		{
		}
	}
}
