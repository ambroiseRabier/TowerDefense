#include "stdafx.h"
#include "../GlobalShared.hpp"
#include "Utils/Event.h"

namespace TowerDefense
{
	/**
	 * \brief Things that are loaded before the start of the game and that I don't intend to destroy.
	 */
	namespace GlobalShared
	{
		sf::Font* default_font;
		sf::Texture* menu_background;
		sf::Texture* default_ui_btn;
		sf::Texture* grass_build_texture;
		sf::Texture* road_walk_texture;
		sf::Texture* spawn_others_texture;
		sf::Texture* castle_others_texture;
		sf::Texture* missing_texture_tile_texture;
		sf::Texture* peon_minion_texture;
		sf::Texture* hpBar_background_texture;
		sf::Texture* hpBar_jauge_texture;
		sf::Texture* stone_tower_texture;

		sf::Texture* level1_btn_texture;
		sf::Texture* level2_btn_texture;
		sf::Texture* level3_btn_texture;
		sf::Texture* pause_btn_texture;
		sf::Texture* play_btn_texture;
		sf::Texture* quit_btn_texture;
		sf::Texture* tower1_btn_texture;
		sf::Texture* tower2_btn_texture;
		sf::Texture* tower3_btn_texture;
		sf::Texture* speedUp_btn_texture;
		sf::Texture* restart_btn_texture;

		sf::Texture* stone_projectile_0_texture;
		sf::Texture* minion_death_texture;
		sf::Texture* castle_death_texture;
		sf::Texture* stone_tower_broken_texture;
		sf::Texture* next_level_btn_texture;
		sf::Texture* freeze_tower_texture;
		sf::Texture* explosiv_tower_texture;
		sf::Texture* freeze_tower_broken_texture;
		sf::Texture* explosiv_tower_broken_texture;
		sf::Texture* freeze_projectile_0_texture;
		sf::Texture* explosiv_projectile_0_texture;

		sf::Texture* tank_minion_texture;
		sf::Texture* heal_minion_texture;
		sf::Texture* tower_1_upgrade_btn_texture;
		sf::Texture* tower_2_upgrade_btn_texture;

		Sharp::Event<void> on_window_close;
		Sharp::Event<void> on_window_close_game_engine_pass;
;
		void destroy()
		{
			delete default_font; default_font = nullptr;
			delete menu_background; menu_background = nullptr;
			delete default_ui_btn; default_ui_btn = nullptr;
			delete grass_build_texture; grass_build_texture = nullptr;
			delete road_walk_texture; road_walk_texture = nullptr;
			delete spawn_others_texture; spawn_others_texture = nullptr;
			delete castle_others_texture; castle_others_texture = nullptr;
			delete missing_texture_tile_texture; missing_texture_tile_texture = nullptr;
			delete peon_minion_texture; peon_minion_texture = nullptr;
			delete hpBar_background_texture; hpBar_background_texture = nullptr;
			delete hpBar_jauge_texture; hpBar_jauge_texture = nullptr;
			delete stone_tower_texture; stone_tower_texture = nullptr;

			delete level1_btn_texture; level1_btn_texture = nullptr;
			delete level2_btn_texture; level2_btn_texture = nullptr;
			delete level3_btn_texture; level3_btn_texture = nullptr;
			delete pause_btn_texture; pause_btn_texture = nullptr;
			delete play_btn_texture; play_btn_texture = nullptr;
			delete quit_btn_texture; quit_btn_texture = nullptr;
			delete tower1_btn_texture; tower1_btn_texture = nullptr;
			delete tower2_btn_texture; tower2_btn_texture = nullptr;
			delete tower3_btn_texture; tower3_btn_texture = nullptr;
			delete speedUp_btn_texture; speedUp_btn_texture = nullptr;
			delete restart_btn_texture; restart_btn_texture = nullptr;

			delete stone_projectile_0_texture; stone_projectile_0_texture = nullptr;
			delete minion_death_texture; minion_death_texture = nullptr;
			delete castle_death_texture; castle_death_texture = nullptr;
			delete stone_tower_broken_texture; stone_tower_broken_texture = nullptr;
			delete next_level_btn_texture; next_level_btn_texture = nullptr;
			delete freeze_tower_texture; freeze_tower_texture = nullptr;
			delete explosiv_tower_texture; explosiv_tower_texture = nullptr;
			delete freeze_tower_broken_texture; freeze_tower_broken_texture = nullptr;
			delete explosiv_tower_broken_texture; explosiv_tower_broken_texture = nullptr;
			delete freeze_projectile_0_texture; freeze_projectile_0_texture = nullptr;
			delete explosiv_projectile_0_texture; explosiv_projectile_0_texture = nullptr;

			delete tank_minion_texture; tank_minion_texture = nullptr;
			delete heal_minion_texture; heal_minion_texture = nullptr;
			delete tower_1_upgrade_btn_texture; tower_1_upgrade_btn_texture = nullptr;
			delete tower_2_upgrade_btn_texture; tower_2_upgrade_btn_texture = nullptr;
		}
	}
}
