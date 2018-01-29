#include "stdafx.h"
#include "Tower.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "Tile.hpp"
#include "GlobalShared.hpp"
#include "GameDesign.hpp"
#include "Projectile.hpp"
#include "Assets.hpp"

using namespace TowerDefense::GameEngine;
namespace TowerDefense
{
	namespace Game
	{
		Tower* Tower::create_stone_tower(const sf::Vector2u& map_pos)
		{
			return new Tower(
				GlobalShared::stone_tower_texture,
				StoneTower,
				map_pos
			);
		}

		Tower::Tower() : params(Constants::GameDesign::towers.at(StoneTower))
		{
			Debug::warn("Tower: default constructor should not be used.");
		}

		Tower::Tower(const sf::Texture* texture, TowerId id, const sf::Vector2u map_pos) 
					: map_pos(map_pos), id(id), params(Constants::GameDesign::towers.at(id))
		{
			set_drawable(static_cast<std::unique_ptr<sf::Drawable>>(
				std::make_unique<sf::Sprite>(*texture)
			));
			z_index = Constants::ZIndex::towers;
			collider = std::make_shared<Collider>(
				Circle(
					params.projectile_params.at(level).range * Constants::Assets::tile_size,
					Constants::Assets::tile_size_half_vec // box in the center of tile.
				),
				Collider::Tag::Tower
			); 
		}

		Tower::~Tower()
		{
		}

		void Tower::init()
		{
			BaseGameObject::init();
			update_position();
		}

		void Tower::on_game_object_overlap(GameObject& game_object)
		{
			if (game_object.get_collider()->tag == Collider::Tag::Minion)
			{
				target = &game_object;
			}
		}

		void Tower::update_position()
		{
			get_transformable().setPosition(
				Tile::map_pos_to_global_pos(map_pos)
			);
		}


		void Tower::shoot()
		{
			assert(target != nullptr);
			Projectile* proj = new Projectile(
				GlobalShared::stone_projectile_0_texture, 
				params.projectile_params.at(level),
				transformable->getPosition() + Constants::Assets::tile_size_half_vec, // could be position of canon
				target->get_transformable().getPosition() + Constants::Assets::tile_size_half_vec
			);
			proj->auto_start();
		}

		unsigned int tempInt=0;
		void Tower::update() {
			tempInt++;
			if (tempInt % 30 == 0 && target != nullptr)
			{
				shoot();
			}
		}

		TowerId Tower::get_tile_id() const
		{
			return id;
		}
	}
}
