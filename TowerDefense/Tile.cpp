#include "stdafx.h"
#include "Tile.hpp"
#include "CastUtils.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"
#include "MapManager.hpp"
#include "AssetsConfig.hpp"

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
			temp_sprite->setTextureRect(sf::IntRect(0,0,Constants::AssetsConfig::tile_size, Constants::AssetsConfig::tile_size));
			sprite = temp_sprite.get();
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
				map_pos_to_global_pos(map_pos)
			);
		}

		TileId Tile::get_tile_id() const
		{
			return id;
		}

		sf::Vector2f Tile::map_pos_to_global_pos(const sf::Vector2u& map_pos)
		{
			return Managers::MapManager::get_map_origin().getPosition() +
				static_cast<sf::Vector2f>(map_pos * Constants::AssetsConfig::tile_size);
		}
	}
}
