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

		/**
		 * \brief 
		 * Delete all global pointer.
		 * Only use this when exiting the game.
		 */
		void destroy();

		void load_all_textures();
		void load_all_sounds();
		sf::Texture* get_texture(const std::string& asset_path);
		sf::SoundBuffer* get_sound_buffer(const std::string& asset_path);
		sf::Sound* get_sound(const std::string& asset_path);
	}
}
#endif
