#pragma once
#ifndef MINION_PARAMS_HPP
#define MINION_PARAMS_HPP

namespace TowerDefense
{
	namespace Game
	{
		struct MinionParams
		{
			/*MinionParams(const MinionParams& other)
				: speed(other.speed),
				  health(other.health),
				  damage(other.damage),
				  money(other.money),
				  heal_others_value(other.heal_others_value),
				  heal_others_delay(other.heal_others_delay)
			{
			}

			MinionParams(MinionParams&& other) noexcept
				: speed(other.speed),
				  health(other.health),
				  damage(other.damage),
				  money(other.money),
				  heal_others_value(other.heal_others_value),
				  heal_others_delay(other.heal_others_delay)
			{
			}

			MinionParams& operator=(const MinionParams& other)
			{
				if (this == &other)
					return *this;
				speed = other.speed;
				health = other.health;
				damage = other.damage;
				money = other.money;
				heal_others_value = other.heal_others_value;
				heal_others_delay = other.heal_others_delay;
				return *this;
			}

			MinionParams& operator=(MinionParams&& other) noexcept
			{
				if (this == &other)
					return *this;
				speed = other.speed;
				health = other.health;
				damage = other.damage;
				money = other.money;
				heal_others_value = other.heal_others_value;
				heal_others_delay = other.heal_others_delay;
				return *this;
			}*/

			MinionParams(
				float speed = 1.f,
				float health = 1.f,
				float damage = 1.f,
				float money = 10.f,
				float heal_others_value = 0.f,
				float heal_others_delay = 0.f,
				unsigned int score = 0.f
			)
				: speed(speed),
				  health(health),
				  damage(damage),
				  money(money),
				  heal_others_value(heal_others_value),
				  heal_others_delay(heal_others_delay),
				  score(score)
			{
			}

			/**
			 * \brief tile/s
			 */
			float speed;
			float health;
			float damage;
			float money;
			/**
			 * \brief value of heal.
			 * note that range depend on healer hitbox.
			 */
			float heal_others_value;
			/**
			 * \brief delay in seconds before each heal.
			 * note that range depend on healer hitbox.
			 */
			float heal_others_delay;
			unsigned int score;
		};

		inline void from_json(json j, MinionParams& p)
		{
			p.speed = j.at("speed").get<float>();
			p.health = j.at("health").get<float>();
			p.damage = j.at("damage").get<float>();
			p.money = j.at("money").get<float>();
			p.heal_others_value = j.at("heal_others_value").get<float>();
			p.heal_others_delay = j.at("heal_others_delay").get<float>();
			p.score = j.at("score").get<unsigned int>();
		}
	}
}
#endif
