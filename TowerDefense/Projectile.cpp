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
#include "GameEngine/Debug.hpp"

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
				sf::Vector2f(0,0), // change collider and do a collision test for aera effect.
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
				const Minion* minion = dynamic_cast<Minion*>(&game_object);
				assert(minion);
				const bool minion_is_dead = minion->get_health().damage(params.damage);
				if (minion_is_dead)
				{
					on_kill();
				}
				// disabling collider so we don't collide anything else.
				collider->gameobject_enabled = false;
				destroy_self();
			}
		}

		void Projectile::update()
		{
			transformable->setPosition(
				transformable->getPosition() + dir * params.speed * (Managers::GameManager::get_delta_time() * Constants::AssetsConfig::tile_size) 
			);
		}

		void Projectile::destroy_self()
		{
			// cancel auto-destroy timer
			Utils::Timer::cancel_destroy(destroy_timer_id);
			// disabled the object (will be destroyed before next update, but this is god pratice)
			isActive = false;
			// Add to destroy juste before rendering.
			// you cannot destroy inside update or collision callback (iterator problem :/)
			Destroyer::destroy_end_of_frame(this);
		}
	}
}
