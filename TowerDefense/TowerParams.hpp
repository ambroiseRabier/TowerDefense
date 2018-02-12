#pragma once
#ifndef TOWER_PARAMS_HPP
#define TOWER_PARAMS_HPP
#include "ProjectileParams.hpp"

namespace TowerDefense
{
	namespace Game
	{
		struct TowerParams
		{
			TowerParams(const std::vector<ProjectileParams>& projectile_params={})
				: projectile_params(projectile_params)
			{
			}

			/**
			 * \brief What the tower shoot.
			 * first projectile params is also cost of tower itself.
			 */
			std::vector<ProjectileParams> projectile_params;
		};

		inline void from_json(json j, TowerParams& p)
		{
			p.projectile_params = j.at("projectile_params").get<std::vector<ProjectileParams>>();
		}
	}
}
#endif
