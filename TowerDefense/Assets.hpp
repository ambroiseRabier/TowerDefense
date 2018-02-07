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
			const std::string hpBar_jauge = "Assets/healthbar_jauge.png";
			const std::string level_background = "Assets/level_background.png";
			const std::string menu_background = "Assets/menu_background.png";


			const std::vector<std::string> all_assets_textures {
				missing_texture_tile,
				hpBar_jauge,
				level_background,
				menu_background,
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
				UIAssets::stone_tower_btn,
				UIAssets::freeze_tower_btn,
				UIAssets::explosiv_tower_btn,
				UIAssets::next_level_btn,
				TowerAssets::stone_tower,
				TowerAssets::stone_tower_broken,
				TowerAssets::stone_tower_build,
				TowerAssets::freeze_tower,
				TowerAssets::freeze_tower_broken,
				TowerAssets::freeze_tower_build,
				TowerAssets::explosiv_tower,
				TowerAssets::explosiv_tower_broken,
				TowerAssets::explosiv_tower_build,
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
				TileAssets::moutain_deco,
				TileAssets::castle_death,
			};
		}
	}
}
#endif