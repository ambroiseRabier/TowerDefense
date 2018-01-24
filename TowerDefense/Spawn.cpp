#include "stdafx.h"
#include "Spawn.hpp"
#include "CastUtils.hpp"
#include "GlobalShared.hpp"
#include "Config.hpp"

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
