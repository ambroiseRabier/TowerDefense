#pragma once
#ifndef MINION_PARAMS_HPP
#define MINION_PARAMS_HPP

namespace TowerDefense
{
	namespace Game
	{
		struct MinionParams
		{
			MinionParams(
				const float speed = 1.f,
				const float health = 1.f,
				const float damage = 1.f,
				const float money = 10.f,
				const float heal_others_value = 0.f,
				const float heal_others_delay = 0.f
			)
				: speed(speed),
				  health(health),
				  damage(damage),
				  money(money), 
				  heal_others_value(heal_others_value), 
				  heal_others_delay(heal_others_delay)
			{
			}

			/**
			 * \brief tile/s
			 */
			const float speed;
			const float health;
			const float damage;
			const float money;
			/**
			 * \brief value of heal.
			 * note that range depend on healer hitbox.
			 */
			const float heal_others_value;
			/**
			 * \brief delay in seconds before each heal.
			 * note that range depend on healer hitbox.
			 */
			const float heal_others_delay;
		};
	}
}
#endif
