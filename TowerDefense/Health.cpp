#include "stdafx.h"
#include "Health.hpp"
#include "../../CastUtils.hpp"
#include "GameEngine/Debug.hpp"
#include "GlobalShared.hpp"
#include "Config.hpp"
#include "AssetsConfig.hpp"
#include "Assets.hpp"

namespace TowerDefense
{
	namespace Game
	{
		class IHasHealth { // todo implements
		   public:
			// pure virtual function
			virtual Health& get_health() = 0;
		};

		Health::Health(const float maxHealth) : maxHealth(maxHealth), actualHealth(maxHealth)
		{
			std::unique_ptr<sf::Sprite> my_sprite_jauge = std::make_unique<sf::Sprite>(*GlobalShared::get_texture(Constants::Assets::hpBar_jauge));
			my_sprite_jauge->setPosition(-25.f, 0); // centered, temp
			sprite_jauge = my_sprite_jauge.get();
			set_drawable(
				std::move(static_cast_ptr<sf::Drawable>(
					my_sprite_jauge
				))
			);
			z_index = Constants::ZIndex::hpBars_jauge;
		}

		bool Health::damage(float value)
		{
			Debug::assert_m(value > 0, "Health: damage value should be positiv and not egal to 0.");
			actualHealth = std::max(0.f, actualHealth - value);
			setGraphismScale();
			if (actualHealth == 0.f)  // NOLINT
			{
				on_death();
				return true;
			}
			return false;
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

		void Health::update_health_pos(const sf::Transformable& relativ_to)
		{
			const sf::Vector2f offset(0, -25.f); // from center of tile.
			transformable->setPosition(
				relativ_to.getPosition() + Constants::AssetsConfig::tile_size_half_vec + offset
			);
		}

		const float& Health::get_health() const
		{
			return actualHealth;
		}
	}
}
