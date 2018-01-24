#include "stdafx.h"
#include "Health.hpp"
#include "../../CastUtils.hpp"
#include "GameEngine/Debug.hpp"
#include "GlobalShared.hpp"
#include "Config.hpp"

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
			Debug::assert_m(value > 0, "Health: healing value should be positiv and not egal to 0.");
			actualHealth = std::min(actualHealth + value, maxHealth);
			setGraphismScale();
		}

		void Health::setGraphismScale() {
			const float lScale = actualHealth / maxHealth;
			Debug::assert_m(lScale >=0 && lScale <= 1, "actualHealth / maxHealth should give a value between 0 and 1 included.");
			sprite_jauge->setScale(lScale, 1);
		}

		const float& Health::get_health()
		{
			return actualHealth;
		}
	}
}
