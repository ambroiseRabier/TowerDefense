#include "stdafx.h"
#include "Constants.hpp"

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
		Sharp::Event<void> on_window_close;
	}
}
