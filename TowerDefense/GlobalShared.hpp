#pragma once

#ifndef GLOBAL_SHARED_HPP
#define GLOBAL_SHARED_HPP
#include "Utils/Event.h"

namespace TowerDefense
{
	/**
	 * \brief Texture, font, and other assets reference that I need trough the game many times, or that I want to preload.
	 * Guaranted to be setted at main before the Managers init.
	 */
	namespace GlobalShared
	{
		extern sf::Font* default_font;
		extern sf::Texture* menu_background;
		extern sf::Texture* default_ui_btn;
		extern sf::Texture* grass_build_texture;
		extern sf::Texture* road_walk_texture;
		extern sf::Texture* spawn_others_texture;
		extern sf::Texture* castle_others_texture;
		extern sf::Texture* minion_red_texture;
		extern sf::Texture* hpBar_background_texture;
		extern sf::Texture* hpBar_jauge_texture;
		extern sf::Texture* stone_tower_texture;

		extern sf::Texture* level1_btn_texture;
		extern sf::Texture* level2_btn_texture;
		extern sf::Texture* level3_btn_texture;
		extern sf::Texture* pause_btn_texture;
		extern sf::Texture* play_btn_texture;
		extern sf::Texture* quit_btn_texture;
		extern sf::Texture* tower1_btn_texture;
		extern sf::Texture* tower2_btn_texture;
		extern sf::Texture* tower3_btn_texture;
		extern sf::Texture* speedUp_btn_texture;
		extern sf::Texture* restart_btn_texture;

		extern sf::Texture* stone_projectile_0_texture;
		extern sf::Texture* minion_death_texture;
		extern sf::Texture* castle_death_texture;
		extern sf::Texture* stone_tower_broken_texture;
		extern sf::Texture* next_level_btn_texture;

		/**
		 * \brief 
		 * Use this one managers or screen that have static variable having memory on heap.
		 * You could use it to save something quickly before exiting.
		 */
		extern Sharp::Event<void> on_window_close;
		
		/**
		 * \brief 
		 * This is reserved for GameEngine. (could be for destroying manager if they were singleton).
		 * (Anything outside of the scope of the game tower defense itself.
		 */
		extern Sharp::Event<void> on_window_close_game_engine_pass;
		extern sf::Texture* missing_texture_tile_texture;

		/**
		 * \brief 
		 * Delete all global pointer.
		 * Only use this when exiting the game.
		 */
		void destroy();
	}
}
#endif
