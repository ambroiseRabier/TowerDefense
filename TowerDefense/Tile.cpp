#include "stdafx.h"
#include "Tile.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "MapManager.hpp"
#include "AssetsConfig.hpp"
#include "TileAssets.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Tile::Tile() : map_pos(sf::Vector2u(0,0))
		{
			Debug::warn("Tile: This default constructor is not supposed to be used.");
		}

		Tile::Tile(TileId id, const sf::Vector2u map_pos): map_pos(map_pos), id(id)
		{
			// force the sprite to the good size. (not tested)
			auto temp_sprite = std::make_shared<sf::Sprite>(
				*Constants::TileAssets::get_tile_texture(id)
			);
			temp_sprite->setTextureRect(sf::IntRect(0,0,Constants::AssetsConfig::tile_size, Constants::AssetsConfig::tile_size));
			sprite = temp_sprite.get();
			set_drawable(std::move(temp_sprite));
			z_index = Constants::ZIndex::tile_background;
		}

		void Tile::init()
		{
			BaseGameObject::init();
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
