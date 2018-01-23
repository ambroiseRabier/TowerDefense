#include "stdafx.h"
#include "Castle.hpp"
#include "Constants.hpp"
#include "CastUtils.hpp"

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
