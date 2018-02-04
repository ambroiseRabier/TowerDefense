#include "stdafx.h"
#include "Castle.hpp"
#include "GlobalShared.hpp"
#include "GameDesign.hpp"
#include "AssetsConfig.hpp"
#include "TileAssets.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Castle::Castle(const sf::Vector2u map_pos) : Tile(Castle_Other, map_pos)
		{
			collider = std::make_shared<GameEngine::Collider>(
				sf::FloatRect(
					0.f,
					0.f,
					Constants::AssetsConfig::tile_size_f,
					Constants::AssetsConfig::tile_size_f
				),
				GameEngine::Collider::Tag::Castle
			);
			collider->mouse_enabled = false;
			health = std::make_unique<Health>(std::max(1.f, Constants::GameDesign::castle_life));
			health->auto_start();
		}

		Castle::~Castle()
		{
			health.reset(nullptr);
		}

		void Castle::init()
		{
			Tile::init();
			// we won't need to remove listener to ondeath since health is destroyed first.
			health->on_death += Sharp::EventHandler::Bind(&Castle::on_death, this);
		}

		Health& Castle::get_health() const
		{
			return *health;
		}

		void Castle::update_position()
		{
			Tile::update_position();
			health->update_health_pos(*transformable, *sprite);
		}

		// ReSharper disable once CppMemberFunctionMayBeConst
		void Castle::on_death()
		{
			//we can keep collision enabled or disable it, any choice is ok.
			// but might be more funny if disabled
			collider->gameobject_enabled = false;
			sprite->setTexture(*GlobalShared::get_texture(Constants::TileAssets::castle_death));
		}
	}
}
