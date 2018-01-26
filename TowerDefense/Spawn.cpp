#include "stdafx.h"
#include "Spawn.hpp"
#include "CastUtils.hpp"
#include "GlobalShared.hpp"
#include "Config.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Spawn::Spawn(const sf::Vector2u map_pos) : Tile(GlobalShared::spawn_others_texture, Spawn_Other, map_pos)
		{
		}
	}
}
