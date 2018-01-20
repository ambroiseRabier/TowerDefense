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
		class Health : TowerDefense::GameEngine::BaseGameObject
		{
		public:
			Health();
			~Health();
			float money_on_death = 0;
			void damage(float value);
			void heal(float value);
			const float& get_health();
			/**
			 * \brief When health is at 0 or beyond, send an event with money_on_death value.
			 */
			static Sharp::Event<float> on_death;
		private:
			float health;
		};
	}
}
#endif
