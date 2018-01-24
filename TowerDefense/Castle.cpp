#include "stdafx.h"
#include "Castle.hpp"
#include "CastUtils.hpp"
#include "GlobalShared.hpp"
#include "Config.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Castle::Castle()
		{
			set_drawable(static_cast_ptr<sf::Drawable>(std::make_unique<sf::Sprite>(*GlobalShared::castle_others_texture)));
			z_index = Constants::ZIndex::tile_background;
			id = Castle_Other;
		}
	}
}
