#pragma once
#include <string>

namespace TowerDefense
{
	namespace Constants
	{
		const std::string game_name = "TowerDefense"; // if you change this, you probably need to change namespaces ;)
		const unsigned int fps_limit = 144;
		namespace Assets
		{
			const std::string loading_background = "Assets/loading_background_inverted.png";
			const std::string default_ui_btn = "Assets/orange_btn.jpg";
			const std::string default_font = "Assets/Inconsolata-Regular.ttf";
		}
	}
	namespace GlobalShared
	{
		/**
		 * \brief Guaranted to be setted at main before the Managers init
		 */
		sf::Font* default_font;
	}
}
