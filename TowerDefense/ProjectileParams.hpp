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
				float reload_delay = 1.f,
				float speed = 1.f,
				float damage = 1.f,
				float range = 10.f,
				float freeze_factor = 0.f,
				float radius_effect = 0.f,
				float upgrade_cost = 0.f)
				: reload_delay(reload_delay),
				  speed(speed),
				  damage(damage),
				  range(range),
				  freeze_factor(freeze_factor),
				  damage_radius(radius_effect),
				  price(upgrade_cost),
				  life_time(std::min(30.f, range / speed)) 

			{
			}

			/**
			 * \brief Seconds. (min is 0 for each frame, not recommended)
			 */
			float reload_delay;
			/**
			 * \brief tile/s
			 */
			float speed;
			/**
			 * \brief 
			 */
			float damage;
			/**
			 * \brief tile (min is 0.5f)
			 */
			float range;
			/**
			 * \brief % (infinite duration, might change) (0.f to 1.f)
			 */
			float freeze_factor;
			/**
			 * \brief m
			 */
			float damage_radius;
			/**
			 * \brief money, cost to have this projectile. First is tower cost also.
			 */
			float price;
			/**
			 * \brief Duration of life of the projectile. 30.f is maximum.
			 * Calculated from range and speed.
			 * In seconds.
			 */
			float life_time;
		};
		
		inline void from_json(json j, ProjectileParams& p)
		{
			p.reload_delay = j.at("reload_delay").get<float>();
			p.speed = j.at("speed").get<float>();
			p.range = j.at("range").get<float>();
			p.freeze_factor = j.at("freeze_factor").get<float>();
			p.damage_radius = j.at("damage_radius").get<float>();
			p.price = j.at("price").get<float>();
		}
	}
}
#endif
