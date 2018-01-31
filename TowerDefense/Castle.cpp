#include "stdafx.h"
#include "Castle.hpp"
#include "GlobalShared.hpp"
#include "GameDesign.hpp"
#include "AssetsConfig.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Castle::Castle(const sf::Vector2u map_pos) : Tile(GlobalShared::castle_others_texture, Castle_Other, map_pos)
		{
			collider = std::make_shared<GameEngine::Collider>(
				sf::FloatRect(0,0, Constants::AssetsConfig::tile_size, Constants::AssetsConfig::tile_size),
				GameEngine::Collider::Tag::Castle
			);
			health = std::make_unique<Health>(std::max(1.f, Constants::GameDesign::castle_life));
			health->auto_start();
		}

		Castle::~Castle()
		{
			health.reset(nullptr);
		}

		Health& Castle::get_health() const
		{
			return *health;
		}

		void Castle::update_position()
		{
			Tile::update_position();
			health->update_health_pos(*transformable);
		}
	}
}
