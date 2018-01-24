#include "stdafx.h"
#include "Health.hpp"
#include "Constants.hpp"
#include "../../CastUtils.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Health::Health(float hpValue)
		{
			//SetJauge
			std::unique_ptr<sf::Sprite> my_sprite_jauge = std::make_unique<sf::Sprite>(*GlobalShared::hpBar_jauge_texture);

			sprite_jauge = my_sprite_jauge.get();
			set_drawable(
				std::move(static_cast_ptr<sf::Drawable>(
					my_sprite_jauge
					))
			);

			z_index = Constants::ZIndex::hpBars_jauge_start;

			maxHealth = hpValue;
			actualHealth = maxHealth;
		}


		Health::~Health()
		{
		}

		void Health::damage(float value)
		{
			actualHealth -= value;
			setGraphismScale();
		}

		void Health::heal(float value)
		{
			if (actualHealth + value >= maxHealth) {
				actualHealth = maxHealth;
			}
			else
				actualHealth += value;
			setGraphismScale();
		}

		void Health::setGraphismScale() {
			float lScale = actualHealth / maxHealth;
			if(lScale >=0 && lScale <= 1)
				sprite_jauge->setScale(lScale, 1);
		}

		const float& Health::get_health()
		{
			return actualHealth;
		}
	}
}
