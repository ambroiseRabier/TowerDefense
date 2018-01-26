#include "stdafx.h"
#include "Tile.hpp"
#include "CastUtils.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"
#include "Assets.hpp"
#include "MapManager.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Tile::Tile() : map_pos(sf::Vector2u(0,0))
		{
			Debug::warn("Tile: This default constructor is not supposed to be used.");
		}

		Tile::Tile(const sf::Texture* texture, TileId id, const sf::Vector2u map_pos): map_pos(map_pos), id(id)
		{
			// force the sprite to the good size. (not tested)
			auto temp_sprite = std::make_unique<sf::Sprite>(*texture);
			temp_sprite->setTextureRect(sf::IntRect(0,0,Constants::Assets::tile_size, Constants::Assets::tile_size));
			set_drawable(static_cast_ptr<sf::Drawable>(std::move(temp_sprite)));
			z_index = Constants::ZIndex::tile_background;
		}

		void Tile::init()
		{
			BaseGameObject::init();
			// fallback in case someone used Tile default constructor without provind any drawable.
			if (!get_drawable())
			{
				Debug::warn("Tile without parameters should not be used");
				set_drawable(
					static_cast_ptr<sf::Drawable>(std::make_unique<sf::Sprite>(*GlobalShared::missing_texture_tile_texture)));
				z_index = Constants::ZIndex::tile_background;
			}
			update_position();
		}

		void Tile::update_position()
		{
			get_transformable().setPosition(
				Managers::MapManager::get_map_origin().getPosition() + static_cast<sf::Vector2f>(map_pos * Constants::Assets::tile_size)
			);
		}

		TileId Tile::get_tile_id() const
		{
			return id;
		}
	}
}
