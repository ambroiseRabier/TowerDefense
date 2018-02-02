#pragma once
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "ProjectileParams.hpp"
#include "Utils/Event.h"
#include "Minion.hpp"

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
			void on_game_object_overlap(GameObject& game_object) override;
			/**
			 * \brief When the projectile kill something.
			 * (I could return experience, if we add experience in minionParams.
			 */
			Sharp::Event<void> on_kill;
		protected:
			/**
			 * \brief Damage the minion with using projectile params.
			 * \param minion 
			 */
			void damage_minion(Minion* minion);
			void update() override;
			void destroy_self();
		private:
			bool enable_collision_flag;
			bool damage_radius_flag;
			const ProjectileParams params;
			sf::Vector2f dir;
			unsigned int destroy_timer_id;
		};
	}
}
#endif
