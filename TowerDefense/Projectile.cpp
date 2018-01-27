#include "stdafx.h"
#include "Projectile.hpp"
#include "Config.hpp"
#include "ProjectileParams.hpp"
#include "Mathf.hpp"
#include "Managers/GameManager.hpp"
#include "GlobalShared.hpp"

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
			assert(texture);
			set_drawable(static_cast<std::unique_ptr<sf::Drawable>>(
				std::make_unique<sf::Sprite>(*texture)
			));
			z_index = Constants::ZIndex::projectile;
			dir = Utils::look_at_dir(spawn_pos, target_pos);
			transformable->setPosition(spawn_pos);
			transformable->setRotation(Utils::look_at_angle(spawn_pos, target_pos));
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&Projectile::temp, this);
			collider = std::make_shared<Collider>(
				sf::Vector2f(0,0), // needto think to to the aera effect.
				Collider::Tag::Projectile
			);
		}

		Projectile::~Projectile()
		{
		}

		void Projectile::set_tower_p(const Tower& new_tower_ref)
		{
			tower_p = &new_tower_ref;
		}

		void Projectile::on_game_object_overlap(GameObject& game_object)
		{
			if (game_object.get_collider()->tag == Collider::Tag::Minion)
			{
				//damage minion
			}
		}
		void Projectile::update()
		{
			transformable->setPosition(
				dir * params.speed * Managers::GameManager::get_deltaTime()
			);
		}

		void Projectile::temp()
		{
			delete this;
		}

		//void on_game_object_overlap

		// on collide use tower_p to give experience if needed.
	}
}
