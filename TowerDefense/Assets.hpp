#pragma once
#ifndef ASSETS_HPP
#define ASSETS_HPP
#include "UIAssets.hpp"
#include "TowerAssets.hpp"
#include "ProjectileAssets.hpp"
#include "MinionAssets.hpp"
#include "TileAssets.hpp"

namespace TowerDefense
{
	namespace Constants
	{
		/**
		 * \brief Path of the assets (images, sounds, ...)
		 */
		namespace Assets
		{
			const std::string default_font = "Assets/Inconsolata-Regular.ttf";
			const std::string missing_texture_tile = "Assets/Tile/missing_texture.png";
			const std::string hpBar_background = "Assets/healthbar_background.png";
			const std::string hpBar_jauge = "Assets/healthbar_jauge.png";
			const std::string level1_btn = "Assets/level1_btn.png";
			const std::string level2_btn = "Assets/level2_btn.png";
			const std::string level3_btn = "Assets/level3_btn.png";
			const std::string tower1_btn = "Assets/tower1_btn.png";
			const std::string tower2_btn = "Assets/tower2_btn.png";
			const std::string tower3_btn = "Assets/tower3_btn.png";
			// faire vector des assets et boucle for pr load.
			const std::string castle_death = "Assets/Tile/castle_negated_destroyed.png";
			const std::string next_level_btn = "Assets/Ui/next_level_btn.png";


			const std::vector<std::string> all_assets_textures {
				missing_texture_tile,
				UIAssets::loading_background,
				UIAssets::menu_background,
				UIAssets::default_ui_btn,
				UIAssets::pause_btn,
				UIAssets::play_btn,
				UIAssets::quit_btn,
				UIAssets::restart_btn,
				UIAssets::speedUp_btn,
				UIAssets::tower_1_upgrade_btn,
				UIAssets::tower_2_upgrade_btn,
				TowerAssets::stone_tower,
				TowerAssets::stone_tower_broken,
				TowerAssets::freeze_tower,
				TowerAssets::freeze_tower_broken,
				TowerAssets::explosiv_tower,
				TowerAssets::explosiv_tower_broken,
				ProjectileAssets::stone_projectile_0,
				ProjectileAssets::freeze_projectile_0,
				ProjectileAssets::explosiv_projectile_0,
				MinionAssets::peon_minion,
				MinionAssets::tank_minion,
				MinionAssets::heal_minion,
				MinionAssets::minion_death,
				TileAssets::castle_others,
				TileAssets::spawn_others,
				TileAssets::road_walk,
				TileAssets::grass_build,
			};
		}
	}
}
#endif