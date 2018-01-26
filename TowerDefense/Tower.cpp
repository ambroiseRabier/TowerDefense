#include "stdafx.h"
#include "Tower.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "Tile.hpp"
#include "GlobalShared.hpp"

using namespace TowerDefense::GameEngine;
namespace TowerDefense
{
	namespace Game
	{
		Tower* Tower::create_stone_tower(const sf::Vector2u& map_pos)
		{
			return new Tower(GlobalShared::stone_tower_texture, StoneTower, map_pos);
		}

		Tower::Tower()
		{
			Debug::warn("Tower: default constructor hsould not be used.");
		}

		Tower::Tower(const sf::Texture* texture, TowerId id, const sf::Vector2u map_pos) : map_pos(map_pos), id(id)
		{
			set_drawable(static_cast<std::unique_ptr<sf::Drawable>>(
				std::make_unique<sf::Sprite>(*texture)
			));
			z_index = Constants::ZIndex::towers;
		}

		Tower::~Tower()
		{
		}

		void Tower::init()
		{
			BaseGameObject::init();
			update_position();
		}

		void Tower::update_position()
		{
			get_transformable().setPosition(
				Tile::map_pos_to_global_pos(map_pos)
			);
		}

		TowerId Tower::get_tile_id() const
		{
			return id;
		}
	}
}
