#include "stdafx.h"
#include "Phantom.hpp"
#include "CastUtils.hpp"
#include "TowerAssets.hpp"
#include "MapManager.hpp"
#include "GameEngine/CollisionManager.hpp"
#include "AssetsConfig.hpp"
#include "Assets.hpp"

using namespace TowerDefense::Managers;
namespace TowerDefense
{
	namespace Game
	{
		Phantom::Phantom()
		{
			auto temp_sprite = std::make_unique<sf::Sprite>(
				*GlobalShared::get_texture(Constants::Assets::missing_texture_tile)
			);
			sprite = temp_sprite.get();
			set_drawable(static_cast_ptr<sf::Drawable>(
				std::move(temp_sprite)
			));
			z_index = Constants::ZIndex::phantom_tower;
			collider = std::make_shared<Collider>(
				sf::FloatRect(
					0,
					0, 
					Constants::AssetsConfig::tile_size_f,
					Constants::AssetsConfig::tile_size_f
				),
				Collider::Tag::UI
			);
			collider->gameobject_enabled = false;
		}

		void Phantom::set_tower_id(TowerId new_tower_id)
		{
			tower_id = new_tower_id;
			sprite->setTexture(*Constants::TowerAssets::get_tower_build_texture(tower_id), true);
		}

		void Phantom::update()
		{
			// isBuildable from mapmanager todo
			update_position();
		}

		void Phantom::on_mouse_click_front(bool left)
		{
			if (left)
			{
				const auto map_pos = MapManager::point_to_map_pos(CollisionManager::mouse_position);
				const bool valid_pos = MapManager::map_pos_exist(map_pos) && MapManager::map_pos_buildable(map_pos);
				if (valid_pos)
				{
					// since map_pos is valid it has to be unsigned integer.
					valid_map_pos = static_cast<sf::Vector2u>(map_pos);
					on_click_valid();
				}
			} 
			else
			{
				on_click_cancel();
			}
		}

		void Phantom::update_position()
		{
			const sf::Vector2i map_pos_raw(MapManager::point_to_map_pos(CollisionManager::mouse_position));
			get_transformable().setPosition(
				static_cast<sf::Vector2f>(map_pos_raw)
				* Constants::AssetsConfig::tile_size_f
				+ MapManager::get_map_origin().getPosition() // to global
			);
		}
	}
}
