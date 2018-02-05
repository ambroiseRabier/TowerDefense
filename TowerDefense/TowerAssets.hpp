#pragma once
#ifndef TOWER_ASSETS_HPP
#define TOWER_ASSETS_HPP
#include "Tower.hpp"
#include "GlobalShared.hpp"
#include "AssetsConfig.hpp"

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
			const std::string stone_tower_build = "Assets/Tower/stone_tower_build.png";
			const std::string freeze_tower_build = "Assets/Tower/freeze_tower_build.png";
			const std::string explosiv_tower_build = "Assets/Tower/explosiv_tower_build.png";
			const sf::IntRect tower_build_frame_valid(0,0, AssetsConfig::tile_size, AssetsConfig::tile_size);
			const sf::IntRect tower_build_frame_invalid(AssetsConfig::tile_size, 0, AssetsConfig::tile_size, AssetsConfig::tile_size);

			const std::unordered_map<Game::TowerId, std::vector<std::string>> tower_id_level_map {
				{Game::TowerId::StoneTower, {stone_tower, stone_tower, stone_tower}},
				{Game::TowerId::FreezeTower, {freeze_tower, freeze_tower, freeze_tower}},
				{Game::TowerId::ExplosivTower, {explosiv_tower, explosiv_tower, explosiv_tower}},
			};

			const std::unordered_map<Game::TowerId, std::string> tower_id_build_map {
				{Game::TowerId::StoneTower, stone_tower_build},
				{Game::TowerId::FreezeTower, freeze_tower_build},
				{Game::TowerId::ExplosivTower, explosiv_tower_build},
			};

			const std::unordered_map<Game::TowerId, std::string> tower_id_broken_map {
				{Game::TowerId::StoneTower, stone_tower_broken},
				{Game::TowerId::FreezeTower, freeze_tower_broken},
				{Game::TowerId::ExplosivTower, explosiv_tower_broken},
			};

			const std::unordered_map<Game::TowerId, std::pair<sf::Color, float>> tower_id_range_map {
				{Game::TowerId::StoneTower, {sf::Color::Blue, 1.f}},
				{Game::TowerId::FreezeTower, {sf::Color::Blue, 1.f}},
				{Game::TowerId::ExplosivTower, {sf::Color::Blue, 1.f}},
			};

			inline sf::Texture* get_tower_texture(Game::TowerId tower_id, const unsigned int& level=0)
			{
				return GlobalShared::get_texture(tower_id_level_map.at(tower_id).at(level));
			}

			inline sf::Texture* get_broken_tower_texture(Game::TowerId tower_id)
			{
				return GlobalShared::get_texture(tower_id_broken_map.at(tower_id));
			}

			inline sf::Texture* get_tower_build_texture(Game::TowerId tower_id)
			{
				return GlobalShared::get_texture(tower_id_build_map.at(tower_id));
			}

			inline std::pair<sf::Color, float> get_tower_range_feedback(Game::TowerId tower_id)
			{
				return tower_id_range_map.at(tower_id);
			}


		}
	}
}
#endif

