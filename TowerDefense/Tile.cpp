#include "stdafx.h"
#include "Tile.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Tile::Tile()
		{
		}

		Tile::Tile(const sf::Texture* texture)
		{
		}


		Tile::~Tile()
		{
		}

		const TileId Tile::get_tile_id() const
		{
			return id;
		}
	}
}
