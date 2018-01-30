#include "stdafx.h"
#include "Tower.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "Tile.hpp"
#include "GlobalShared.hpp"
#include "GameDesign.hpp"
#include "Projectile.hpp"
#include "Assets.hpp"
#include "Timer.hpp"

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
			if (shoot_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(shoot_time_out_id);
			}
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
				//todo take first or last?
				target = &game_object;
				if (shoot_time_out_id == 0)
				{
					// instant shoot then use a time_out to forbid shooting for a reload_delay duration.
					shoot();
					shoot_time_out_id = Utils::Timer::set_time_out(
						Sharp::EventHandler::Bind(&Tower::reset_shoot_delay, this),
						get_current_projectile_params().reload_delay
					);
				}
			}
		}

		void Tower::update_position()
		{
			get_transformable().setPosition(
				Tile::map_pos_to_global_pos(map_pos)
			);
		}

		void Tower::shoot() const 
		{
			// if target has become null in meantime don't shoot. 
			// (destroyed by another tower or out of range, or died on castle)
			if (target == nullptr) 
				return;

			Projectile* proj = new Projectile(
				GlobalShared::stone_projectile_0_texture, 
				get_current_projectile_params(),
				transformable->getPosition() + Constants::Assets::tile_size_half_vec, // could be position of canon
				target->get_transformable().getPosition() + Constants::Assets::tile_size_half_vec
			);
			proj->auto_start();
			// DONT WORRY: no memory leak, Timer class take care of it.
			// might not be adapted to pooling however
		}

		void Tower::reset_shoot_delay()
		{
			// reset the id of time_out to "null" value so we can shoot again.
			shoot_time_out_id = 0;
		}

		void Tower::on_projectile_kill()
		{
			// todo call it.
			// todo: but you have to think of two use case:
			// tower is destroyed before the projectile
			// projectile is destroyed before the tower.
		}

		TowerId Tower::get_tile_id() const
		{
			return id;
		}

		const ProjectileParams& Tower::get_current_projectile_params() const
		{
			return params.projectile_params.at(level);
		}
	}
}
