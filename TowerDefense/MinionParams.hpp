#pragma once
#ifndef MINION_PARAMS_HPP
#define MINION_PARAMS_HPP

namespace TowerDefense
{
	namespace Game
	{
		struct MinionParams
		{
			MinionParams(const float speed = 1.f, const float health = 1.f, const float damage = 1.f, const float money = 10.f, const float life_time = 5.f)
				: speed(speed),
				  health(health),
				  damage(damage),
				  money(money),
				  life_time(std::min(30.f, life_time))
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
			 * \brief Duration of life of the projectile. 30.f is maximum.
			 * In seconds.
			 */
			const float life_time;
		};
	}
}
#endif
