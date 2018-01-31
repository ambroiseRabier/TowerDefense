#include "stdafx.h"
#include "Tower.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "Tile.hpp"
#include "GlobalShared.hpp"
#include "GameDesign.hpp"
#include "Projectile.hpp"
#include "Timer.hpp"
#include "AssetsConfig.hpp"
#include "CastUtils.hpp"

using namespace TowerDefense::GameEngine;
namespace TowerDefense
{
	namespace Game
	{
		Tower* Tower::create_stone_tower(const Vector2u& map_pos)
		{
			return new Tower(
				GlobalShared::stone_tower_texture,
				StoneTower,
				map_pos
			);
		}

		Tower* Tower::create_freeze_tower(const Vector2u& map_pos)
		{
			return new Tower(
				GlobalShared::freeze_tower_texture,
				FreezeTower,
				map_pos
			);
		}

		Tower* Tower::create_explosiv_tower(const Vector2u& map_pos)
		{
			return new Tower(
				GlobalShared::explosiv_tower_texture,
				ExplosivTower,
				map_pos
			);
		}

		Tower::Tower() : params(Constants::GameDesign::towers.at(StoneTower))
		{
			Debug::warn("Tower: default constructor should not be used.");
		}

		Tower::Tower(const Texture* texture, TowerId id, const Vector2u map_pos) 
					: map_pos(map_pos), id(id), params(Constants::GameDesign::towers.at(id))
		{
			auto temp_sprite = std::make_unique<Sprite>(*texture);
			sprite = temp_sprite.get();
			set_drawable(static_cast_ptr<Drawable>(
				temp_sprite
			));
			z_index = Constants::ZIndex::towers;
			collider = std::make_shared<Collider>(
				Circle(
					std::max(0.5f, params.projectile_params.at(level).range) * Constants::AssetsConfig::tile_size,
					Constants::AssetsConfig::tile_size_half_vec // box in the center of tile.
				),
				Collider::Tag::Tower
			);
			// onclick for tower upgrade?
		}

		Tower::~Tower()
		{
			if (shoot_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(shoot_time_out_id);
				shoot_time_out_id = 0;
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
				transformable->getPosition() + Constants::AssetsConfig::tile_size_half_vec, // could be position of canon
				target->get_transformable().getPosition() + Constants::AssetsConfig::tile_size_half_vec
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

		void Tower::on_game_over()
		{
			if (shoot_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(shoot_time_out_id);
				shoot_time_out_id = 0;
			}
			update_active = false;
			collider->gameobject_enabled = false;
			collider->mouse_enabled = false;
			switch (id)
			{
			case StoneTower: 
				sprite->setTexture(*GlobalShared::stone_tower_broken_texture);
				break;
			case FreezeTower: 
				sprite->setTexture(*GlobalShared::freeze_tower_broken_texture);
				break;
			case ExplosivTower: 
				sprite->setTexture(*GlobalShared::explosiv_tower_broken_texture);
				break;
			default: ;
			}
		}

		const ProjectileParams& Tower::get_current_projectile_params() const
		{
			return params.projectile_params.at(level);
		}
	}
}
