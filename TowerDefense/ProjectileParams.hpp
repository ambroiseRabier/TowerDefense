#pragma once
#ifndef PROJECTILE_PARAMS_HPP
#define PROJECTILE_PARAMS_HPP

namespace TowerDefense
{
	namespace Game
	{
		struct ProjectileParams
		{
			ProjectileParams(
				const float reload_delay = 1.f,
				const float speed = 1.f,
				const float damage = 1.f,
				const float range = 10.f,
				const float freeze_factor = 0.f,
				const float radius_effect = 0.f,
				const float upgrade_cost = 0.f)
				: reload_delay(reload_delay),
				  speed(speed),
				  damage(damage),
				  range(range),
				  freeze_factor(freeze_factor),
				  radius_effect(radius_effect),
				  upgrade_cost(upgrade_cost),
				  life_time(std::min(30.f, range / speed)) 

			{
			}

			/**
			 * \brief Seconds.
			 */
			const float reload_delay;
			/**
			 * \brief tile/s
			 */
			const float speed;
			/**
			 * \brief 
			 */
			const float damage;
			/**
			 * \brief tile (min is 0.5f)
			 */
			const float range;
			/**
			 * \brief % (infinite duration, might change)
			 */
			const float freeze_factor;
			/**
			 * \brief m
			 */
			const float radius_effect;
			/**
			 * \brief money
			 */
			const float upgrade_cost;
			/**
			 * \brief Duration of life of the projectile. 30.f is maximum.
			 * Calculated from range and speed.
			 * In seconds.
			 */
			const float life_time;
		};
	}
}
#endif
