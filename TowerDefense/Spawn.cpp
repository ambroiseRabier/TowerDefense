#include "stdafx.h"
#include "Spawn.hpp"
#include "Constants.hpp"
#include "CastUtils.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Spawn::Spawn()
		{
			set_drawable(static_cast_ptr<sf::Drawable>(std::make_unique<sf::Sprite>(*GlobalShared::spawn_others_texture)));
			z_index = Constants::ZIndex::tile_background;
			id = Spawn_Other;
		}
	}
}
