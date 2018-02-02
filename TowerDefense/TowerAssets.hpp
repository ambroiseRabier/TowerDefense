#pragma once
#ifndef TOWER_ASSETS_HPP
#define TOWER_ASSETS_HPP
#include "Tower.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace Constants
	{
		// I prefer naming it TowerAssets instead of Tower because the editor will confuse it with the Tower class...
		namespace TowerAssets
		{
			const std::string stone_tower = "Assets/Tower/stone_tower.png";
			const std::string stone_tower_broken = "Assets/Tower/stone_tower_broken.png";
			const std::string freeze_tower = "Assets/Tower/freeze_tower.png";
			const std::string freeze_tower_broken = "Assets/Tower/freeze_tower_broken.png";
			const std::string explosiv_tower = "Assets/Tower/freeze_tower.png";
			const std::string explosiv_tower_broken = "Assets/Tower/explosiv_tower_broken.png";

			const std::unordered_map<Game::TowerId, std::vector<std::string>> tower_id_level_map {
				{Game::TowerId::StoneTower, {stone_tower, stone_tower, stone_tower}},
				{Game::TowerId::FreezeTower, {freeze_tower, freeze_tower, freeze_tower}},
				{Game::TowerId::ExplosivTower, {explosiv_tower, explosiv_tower, explosiv_tower}},
			};

			const std::unordered_map<Game::TowerId, std::string> tower_id_broken_map {
				{Game::TowerId::StoneTower, stone_tower_broken},
				{Game::TowerId::FreezeTower, freeze_tower_broken},
				{Game::TowerId::ExplosivTower, explosiv_tower_broken},
			};

			inline sf::Texture* get_tower_texture(Game::TowerId tower_id, const unsigned int& level=0)
			{
				return GlobalShared::get_texture(tower_id_level_map.at(tower_id).at(level));
			}

			inline sf::Texture* get_broken_tower_texture(Game::TowerId tower_id)
			{
				return GlobalShared::get_texture(tower_id_broken_map.at(tower_id));
			}
		}
	}
}
#endif

