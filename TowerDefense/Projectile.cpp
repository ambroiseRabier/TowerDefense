#include "stdafx.h"
#include "Projectile.hpp"
#include "Config.hpp"
#include "ProjectileParams.hpp"
#include "Mathf.hpp"
#include "Managers/GameManager.hpp"
#include "Timer.hpp"
#include "Minion.hpp"
#include "Destroyer.hpp"
#include "AssetsConfig.hpp"

namespace TowerDefense
{
	namespace Game
	{
		/*Projectile* Projectile::create_stone_0_projectile(const sf::Vector2f spawn_pos, const sf::Vector2f& target_pos)
		{
			return new Projectile(GlobalShared::stone_projectile, );
		}*/

		Projectile::Projectile()
		{
		}

		Projectile::Projectile(const sf::Texture* texture, const ProjectileParams params,
							   const sf::Vector2f spawn_pos, const sf::Vector2f& target_pos)
							  : params(params)
		{
			std::unique_ptr<sf::Sprite> sprite_p = std::make_unique<sf::Sprite>(*texture);
			sprite_p->setPosition(
				-sprite_p->getLocalBounds().width/2.f,
				-sprite_p->getLocalBounds().height/2.f
			);
			set_drawable(static_cast<std::unique_ptr<sf::Drawable>>(
				std::move(sprite_p)
			));
			z_index = Constants::ZIndex::projectile;
			dir = Utils::look_at_dir(spawn_pos, target_pos);
			transformable->setPosition(spawn_pos);
			transformable->setRotation(Utils::look_at_angle(spawn_pos, target_pos));
			collider = std::make_shared<Collider>(
				sf::Vector2f(0,0),
				Collider::Tag::Projectile
			);
			collider->mouse_enabled = false;
			destroy_timer_id = Utils::Timer::destroy(static_cast<GameObject*>(this), params.life_time);
		}

		void Projectile::on_game_object_overlap(GameObject& game_object)
		{
			if (game_object.get_collider()->tag == Collider::Tag::Minion)
			{
				//damage minion
				Minion* minion = dynamic_cast<Minion*>(&game_object);
				assert(minion);
				const bool has_damage_radius = params.damage_radius >= 0;
				if (damage_radius_flag)
				{
					// damage any minion that collide.
					damage_minion(minion);
				}
				else if (has_damage_radius)
				{
					// change collider and do a collision test for aera effect next frame.
					collider.reset();
					collider = std::make_shared<Collider>(
						sf::Vector2f(0,0), 
						params.damage_radius,
						Collider::Tag::Projectile
					);
					enable_collision_flag = true;
					damage_radius_flag = true;
					// disabling collider, if we were to keep it, it would only colldier part of minions
					// it's better to wait next frame  and do full collisions. Minions will have moved but it's ok.
					collider->gameobject_enabled = false;
					// bug: auto-destroy timer could tick right there and it would cancel
					// the aera effect, but if I cancel the timer here and the user quit
					// then no one has the pointer and memory leak :/ (bad design somewhere ^^)
				}
				else
				{
					damage_minion(minion);
					destroy_self();
					// disabling collider so we don't collide anything else.
					collider->gameobject_enabled = false;
				}
			}
		}

		void Projectile::damage_minion(Minion* minion)
		{
			const bool minion_is_dead = minion->get_health().damage(params.damage);
			if (minion_is_dead)
			{
				on_kill();
			}
			else
			{
				if (params.freeze_factor > 0)
				{
					minion->freeze(
						std::min(1.f, std::max(0.f, params.freeze_factor))
					);
				}
			}
		}

		void Projectile::update()
		{
			// only move if we are not on damage radius special frame.
			if (!damage_radius_flag)
			{
				transformable->setPosition(
					transformable->getPosition() + dir * params.speed * (Managers::GameManager::get_delta_time() * Constants::
						AssetsConfig::tile_size)
				);
			} 
			else
			{
				// we will do collision after update and the projectile die at the end of frame.
				destroy_self();
			}
			if (enable_collision_flag)
			{
				collider->gameobject_enabled = true;
				enable_collision_flag = false;
			}
		}

		void Projectile::destroy_self()
		{
			// cancel auto-destroy timer
			Utils::Timer::cancel_destroy(destroy_timer_id);
			// todo: add another destroy timer and do some animation of projectile hit.

			// Add to destroy juste before rendering.
			// you cannot destroy inside update or collision callback (iterator problem :/)
			Destroyer::destroy_end_of_frame(this);
		}
	}
}
