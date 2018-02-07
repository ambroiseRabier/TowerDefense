#pragma once
#ifndef PROJECTILE_ASSETS_HPP
#define PROJECTILE_ASSETS_HPP

namespace TowerDefense
{
	namespace Constants
	{
		namespace ProjectileAssets
		{
			const std::string stone_projectile_0 = "Assets/Projectile/stone_projectile_0.png";
			const std::string freeze_projectile_0 = "Assets/Projectile/freeze_projectile_0.png";
			const std::string explosiv_projectile_0 = "Assets/Projectile/explosiv_projectile_0.png";
			
			const std::unordered_map<Game::TowerId, std::vector<std::string>> tower_id_level_map {
				{Game::TowerId::StoneTower, {stone_projectile_0, stone_projectile_0, stone_projectile_0}},
				{Game::TowerId::FreezeTower, {freeze_projectile_0, freeze_projectile_0, freeze_projectile_0}},
				{Game::TowerId::ExplosivTower, {explosiv_projectile_0, explosiv_projectile_0, explosiv_projectile_0}},
			};

			inline sf::Texture* get_projectile_texture(Game::TowerId tower_id, const unsigned int& level=0)
			{
				return GlobalShared::get_texture(tower_id_level_map.at(tower_id).at(level));
			}
		}
	}
}
#endif

