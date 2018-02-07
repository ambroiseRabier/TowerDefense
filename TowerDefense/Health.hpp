#pragma once
#ifndef HEALTH_HPP
#define HEALTH_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "Utils/Event.h"

namespace TowerDefense
{
	namespace Game
	{
		/**
		 * \brief Contain health logic and the health bar.
		 * Sprite can be partially rendered to reduce healthbar.
		 */
		class Health : public  GameEngine::BaseGameObject
		{
		public:
			Health(const float maxHealth = 1);
			float money_on_death = 0;
			void update() override;
			/**
			 * \brief 
			 * \param value 
			 * \return true if the minion has been killed.
			 */
			bool damage(float value);
			void heal(float value);
			void update_health_pos(const sf::Transformable& relativ_to, const sf::Sprite& relativ_to_sprite);
			const float& get_health() const;
			/**
			 * \brief When health is at 0 or beyond, send an event.
			 */
			Sharp::Event<void> on_damage;
			Sharp::Event<void> on_death;
		protected:
			void setGraphismScale();
			float maxHealth;
			float actualHealth;
			sf::Sprite* sprite_jauge;
		};
	}
}
#endif
