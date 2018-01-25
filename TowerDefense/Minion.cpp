#include "stdafx.h"
#include "Minion.hpp"
#include "../../CastUtils.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Minion::Minion()
		{
			std::unique_ptr<sf::Sprite> my_sprite = std::make_unique<sf::Sprite>(*GlobalShared::minion_red_texture);

			sprite = my_sprite.get();
			set_drawable(
				std::move(static_cast_ptr<sf::Drawable>(
					my_sprite
				))
			);
			collider = std::make_shared<Collider>(
				sf::FloatRect(0, 0, 50, 50),
				Collider::Tag::Minion
			);
			z_index = Constants::ZIndex::minions_start;
		}

		Minion::~Minion()
		{
		}
	}
}
