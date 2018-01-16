#pragma once
#include <string>

namespace TowerDefense
{
	namespace Constants
	{

		/**
		 * \brief Config for the game.
		 */
		namespace Config
		{
			const std::string game_name = "TowerDefense"; // if you change this, you probably need to change namespaces ;)
			const unsigned int fps_limit = 144;
		}

		/**
		 * \brief Path of the assets (images, sounds, ...)
		 */
		namespace Assets
		{
			const std::string loading_background = "Assets/loading_background_inverted.png";
			const std::string default_ui_btn = "Assets/orange_btn.jpg";
			const std::string default_font = "Assets/Inconsolata-Regular.ttf";
		}
	}
	/**
	 * \brief Texture, font, and other assets reference that I need trough the game many times, or that I want to preload.
	 */
	namespace GlobalShared
	{
		/**
		 * \brief Guaranted to be setted at main before the Managers init
		 */
		sf::Font* default_font;
	}
}
