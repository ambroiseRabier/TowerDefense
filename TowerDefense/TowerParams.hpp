#pragma once
#include "ProjectileParams.hpp"

struct TowerParams
{
	TowerParams(const std::vector<ProjectileParams>& projectile_params)
		: projectile_params(projectile_params)
	{
	}

	/**
	 * \brief What the tower shoot.
	 * first projectile params is also cost of tower itself.
	 */
	const std::vector<ProjectileParams> projectile_params;
};
