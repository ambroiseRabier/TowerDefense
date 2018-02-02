#pragma once

#ifndef ASSETS_HPP
#define ASSETS_HPP

using namespace TowerDefense::GameEngine;
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
			const std::string loading_background = "Assets/loading_background_inverted.png";
			const std::string menu_background = "Assets/menu_background.jpg";
			const std::string default_ui_btn = "Assets/base_btn.png";
			const std::string road_walk = "Assets/Tile/road.png";
			const std::string grass_build = "Assets/Tile/grass.png";
			const std::string spawn_others = "Assets/Tile/spawn.png";
			const std::string castle_others = "Assets/Tile/castle_negated.png";
			const std::string missing_texture_tile = "Assets/Tile/missing_texture.png";
			const std::string peon_minion = "Assets/Minion/peon_minion.png";
			const std::string hpBar_background = "Assets/healthbar_background.png";
			const std::string hpBar_jauge = "Assets/healthbar_jauge.png";
			const std::string stone_tower = "Assets/Tower/stone_tower.png";

			const std::string level1_btn = "Assets/level1_btn.png";
			const std::string level2_btn = "Assets/level2_btn.png";
			const std::string level3_btn = "Assets/level3_btn.png";
			const std::string pause_btn = "Assets/pause_btn.png";
			const std::string play_btn = "Assets/play_btn.png";
			const std::string quit_btn = "Assets/quit_btn.png";
			const std::string tower1_btn = "Assets/tower1_btn.png";
			const std::string tower2_btn = "Assets/tower2_btn.png";
			const std::string tower3_btn = "Assets/tower3_btn.png";
			const std::string restart_btn = "Assets/retry_btn.png";
			const std::string speedUp_btn = "Assets/speedUp_btn.png";
			// faire vector des assets et boucle for pr load.
			const std::string stone_projectile_0 = "Assets/Projectile/stone_projectile_0.png";
			const std::string minion_death = "Assets/Minion/minion_death.png";
			const std::string castle_death = "Assets/Tile/castle_negated_destroyed.png";
			const std::string stone_tower_broken = "Assets/Tower/stone_tower_broken.png";
			const std::string next_level_btn = "Assets/Ui/next_level_btn.png";
			const std::string freeze_tower = "Assets/Tower/freeze_tower.png";
			const std::string explosiv_tower = "Assets/Tower/freeze_tower.png";
			const std::string freeze_tower_broken = "Assets/Tower/freeze_tower_broken.png";
			const std::string explosiv_tower_broken = "Assets/Tower/explosiv_tower_broken.png";
			const std::string freeze_projectile_0 = "Assets/Projectile/freeze_projectile_0.png";
			const std::string explosiv_projectile_0 = "Assets/Projectile/explosiv_projectile_0.png";

			const std::string tank_minion = "Assets/Minion/tank_minion.png";
			const std::string heal_minion = "Assets/Minion/heal_minion.png";
			const std::string tower_1_upgrade_btn = "Assets/Ui/tower_1_upgrade_btn.png"; // start from 1 since 0 is base tower
			const std::string tower_2_upgrade_btn = "Assets/Ui/tower_2_upgrade_btn.png";
		}
	}
}
#endif