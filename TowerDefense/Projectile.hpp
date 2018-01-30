#pragma once
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "ProjectileParams.hpp"
#include "Tower.hpp"

namespace TowerDefense
{
	namespace Game
	{
		class Projectile : public GameEngine::BaseGameObject
		{
		public:
			Projectile();
			/**
			 * \brief 
			 * \param texture 
			 * \param params 
			 * \param spawn_pos
			 * \param target_pos 
			 */
			Projectile(const sf::Texture* texture, const ProjectileParams params, const sf::Vector2f spawn_pos,
			           const sf::Vector2f& target_pos);
			void set_tower_p(const Tower& new_tower_ref);
			void on_game_object_overlap(GameObject& game_object) override;
		protected:
			void update() override;
			void destroy_self();
		private:
			const ProjectileParams params;
			sf::Vector2f dir;
			const Tower* tower_p;
			unsigned int destroy_timer_id;
		};
	}
}
#endif
