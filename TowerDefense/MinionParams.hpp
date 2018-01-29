#pragma once
#ifndef MINION_PARAMS_HPP
#define MINION_PARAMS_HPP

namespace TowerDefense
{
	namespace Game
	{
		struct MinionParams
		{
			MinionParams(const float speed = 1.f, const float health = 1.f, const float damage = 1.f, const float money = 10.f)
				: speed(speed),
				  health(health),
				  damage(damage),
				  money(money)
			{
			}

			/**
			 * \brief tile/s
			 */
			const float speed;
			const float health;
			const float damage;
			const float money;
		};
	}
}
#endif
