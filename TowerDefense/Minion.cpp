#include "stdafx.h"
#include "Minion.hpp"
#include "Constants.hpp"
#include "../../CastUtils.hpp"
#include "GameEngine/Debug.hpp"

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
				std::make_unique<sf::FloatRect>(sf::FloatRect(0, 0, 50, 50)),
				Collider::Tag::Minion
				);
			collider->tag = Collider::Tag::Minion;
			z_index = Constants::ZIndex::minions_start;
		}

		Minion::~Minion()
		{
		}
	}
}
