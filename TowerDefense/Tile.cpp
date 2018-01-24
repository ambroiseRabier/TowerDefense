#include "stdafx.h"
#include "Tile.hpp"
#include "CastUtils.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Tile::Tile()
		{
		}

		Tile::Tile(const sf::Texture* texture, TileId id): id(id)
		{
			set_drawable(static_cast_ptr<sf::Drawable>(std::make_unique<sf::Sprite>(*texture)));
			z_index = Constants::ZIndex::tile_background;
		}

		void Tile::init()
		{
			BaseGameObject::init();
			// fallback in case someone used Tile default constructor without provind any drawable.
			if (!get_drawable())
			{
				GameEngine::Debug::warn("Tile without parameters should not be used");
				set_drawable(
					static_cast_ptr<sf::Drawable>(std::make_unique<sf::Sprite>(*GlobalShared::missing_texture_tile_texture)));
				z_index = Constants::ZIndex::tile_background;
			}
			/* todo
			Debug::assert_m(
				 == Constants::Assets::tile_size
			);*/
		}

		TileId Tile::get_tile_id() const
		{
			return id;
		}
	}
}
