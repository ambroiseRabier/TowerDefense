#include "stdafx.h"
#include "Phantom.hpp"
#include "TowerAssets.hpp"
#include "MapManager.hpp"
#include "GameEngine/CollisionManager.hpp"
#include "AssetsConfig.hpp"
#include "Assets.hpp"
#include "GameDesign.hpp"

using namespace TowerDefense::Managers;
namespace TowerDefense
{
	namespace Game
	{
		Phantom::Phantom()
		{
			auto temp_sprite = std::make_shared<sf::Sprite>(
				*GlobalShared::get_texture(Constants::Assets::missing_texture_tile)
			);
			auto temp_range_feedback = std::make_shared<sf::CircleShape>();
			range_feedback = temp_range_feedback.get();
			sprite = temp_sprite.get();
			set_drawable(std::move(temp_sprite));
			add_drawable(std::move(temp_range_feedback));
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
			range_feedback->setFillColor(sf::Color::Transparent);
			update_range_feeback();
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

		// copy pasted from Tower.cpp (todo DRY)
		void Phantom::update_range_feeback()
		{
			range_feedback->setPointCount(range_feedback->getPointCount()*2);
			range_feedback->setRadius(calc_collider_circle_radius());
			range_feedback->setPosition(
				-range_feedback->getRadius() + Constants::AssetsConfig::tile_size/2,
				-range_feedback->getRadius() + Constants::AssetsConfig::tile_size/2
			);
			range_feedback->setOutlineColor(Constants::TowerAssets::get_tower_range_feedback(tower_id).first);
			range_feedback->setOutlineThickness(Constants::TowerAssets::get_tower_range_feedback(tower_id).second);
		}

		// copy pasted from Tower.cpp
		float Phantom::calc_collider_circle_radius() const
		{
			// remove one pixel at the end to avoid colliding with border of a tile.
			return std::max(0.5f, Constants::GameDesign::towers.at(tower_id).projectile_params.at(0).range) * Constants::AssetsConfig::tile_size - 1;
		}
	}
}
