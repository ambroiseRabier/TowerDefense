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
		Sharp::Event<void> on_window_close;
	}
}
