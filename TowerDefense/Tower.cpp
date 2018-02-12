#include "stdafx.h"
#include "Tower.hpp"
#include "GameEngine/Debug.hpp"
#include "Config.hpp"
#include "Tile.hpp"
#include "GlobalShared.hpp"
#include "GameDesign.hpp"
#include "Projectile.hpp"
#include "Timer.hpp"
#include "AssetsConfig.hpp"
#include "GameObjects/BaseButton.hpp"
#include "Player.hpp"
#include "UIAssets.hpp"
#include "TowerAssets.hpp"
#include "ProjectileAssets.hpp"
#include "SoundManager.hpp"

using namespace TowerDefense::GameEngine;
using namespace sf;
namespace TowerDefense
{
	namespace Game
	{
		Tower::Tower() : params(GlobalShared::get_gd().towers.at(TowerId::StoneTower))
		{
			Debug::warn("Tower: default constructor should not be used.");
		}

		Tower::Tower(TowerId id, const Vector2u map_pos) 
					: map_pos(map_pos), id(id), params(GlobalShared::get_gd().towers.at(id))
		{
			auto temp_sprite = std::make_shared<Sprite>(
				*Constants::TowerAssets::get_tower_texture(id)	
			);
			auto temp_range_feedback = std::make_shared<CircleShape>();
			sprite = temp_sprite.get();
			range_feedback = temp_range_feedback.get();
			set_drawable(std::move(temp_sprite));
			add_drawable(std::move(temp_range_feedback));
			z_index = Constants::ZIndex::towers;
			collider = std::make_shared<Collider>(
				Circle(
					calc_collider_circle_radius(),
					Constants::AssetsConfig::tile_size_half_vec // box in the center of tile.
				),
				Collider::Tag::Tower
			);
			range_feedback->setFillColor(sf::Color::Transparent);
			update_range_feeback();
			upgrade_btn = std::make_unique<UI::BaseButton>(
				GlobalShared::get_texture(Constants::UIAssets::tower_1_upgrade_btn),
				Constants::ZIndex::tower_upgrade_btn
			);
			on_player_money_change();
			upgrade_btn->auto_start();
			Managers::Player::on_money_change += Sharp::EventHandler::Bind(&Tower::on_player_money_change, this);
			upgrade_btn->on_click += Sharp::EventHandler::Bind(&Tower::upgrade_tower, this);
		}

		Tower::~Tower()
		{
			Managers::Player::on_money_change -= Sharp::EventHandler::Bind(&Tower::on_player_money_change, this);
			if (shoot_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(shoot_time_out_id);
				shoot_time_out_id = 0;
			}
		}

		void Tower::init()
		{
			BaseGameObject::init();
			update_position();
			SoundManager::play_one_shoot(Constants::TowerAssets::get_tower_build_sound(id));
		}

		void Tower::update()
		{
			// using scale as hack to hide/show it.
			range_feedback->setScale(0,0);
		}

		void Tower::on_game_object_overlap(GameObject& game_object)
		{
			if (game_object.get_collider()->tag == Collider::Tag::Minion
			 || game_object.get_collider()->tag == Collider::Tag::HealMinion)
			{
				// take the oldest spawned minion.
				target = &game_object;
				// instant shoot then use a time_out to forbid shooting for a reload_delay duration.
				shoot();
				shoot_time_out_id = Utils::Timer::set_time_out(
					Sharp::EventHandler::Bind(&Tower::reset_shoot_delay, this),
					std::max(0.f, get_current_projectile_params().reload_delay)
				);
				// no need to seek for target in mean time (optimizaiton)
				collider->gameobject_enabled = false;
			}
		}

		void Tower::on_mouse_overlap()
		{
			// using scale as hack to hide/show it.
			range_feedback->setScale(1,1);
		}

		// ReSharper disable once CppMemberFunctionMayBeConst
		void Tower::update_position()
		{
			get_transformable().setPosition(
				Tile::map_pos_to_global_pos(map_pos)
			);
			upgrade_btn->get_transformable().setPosition(
				transformable->getPosition().x + Constants::AssetsConfig::tile_size - upgrade_btn->get_sprite().getLocalBounds().width,
				transformable->getPosition().y
			);
		}

		// ReSharper disable once CppMemberFunctionMayBeConst
		void Tower::on_player_money_change()
		{
			// maybe later state disabled for btn
			// keep the order of the condition !
			upgrade_btn->isActive = !is_max_level() && Managers::Player::can_upgrade_tower(id, level+1); 
		}

		void Tower::shoot() const 
		{
			// note target will never be null since it's is done right after colliding with it.
			Projectile* proj = new Projectile(
				get_current_projectile_texture(), 
				get_current_projectile_params(),
				transformable->getPosition() + Constants::AssetsConfig::tile_size_half_vec, // could be position of canon
				target->get_transformable().getPosition() + Constants::AssetsConfig::tile_size_half_vec
			);
			proj->auto_start();
			SoundManager::play_one_shoot(Constants::TowerAssets::get_tower_shoot_sound(id));
			// DONT WORRY: no memory leak, Timer class take care of it.
			// might not be adapted to pooling however
		}

		void Tower::reset_shoot_delay()
		{
			// reset the id of time_out to "null" value so we can shoot again.
			shoot_time_out_id = 0;
			// re-enabled target seeking.
			collider->gameobject_enabled = true;
		}

		void Tower::on_projectile_kill()
		{
			// todo call it.
			// todo: but you have to think of two use case:
			// tower is destroyed before the projectile
			// projectile is destroyed before the tower.
		}

		float Tower::calc_collider_circle_radius() const
		{
			// remove one pixel at the end to avoid colliding with border of a tile.
			return std::max(0.5f, params.projectile_params.at(level).range) * Constants::AssetsConfig::tile_size - 1;
		}

		void Tower::upgrade_tower()
		{
			assert(!is_max_level());
			if (Managers::Player::can_upgrade_tower(id, level+1))
			{
				level++;
				assert(collider->get_type() == Collider::Type::Circle);
				// update money after leveling up (for on_player_money_change)
				Managers::Player::buy_tower_upgrade(id, level);
				update_range_feeback();
				collider->set_circle(
					Constants::AssetsConfig::tile_size_half_vec,
					calc_collider_circle_radius()
				);
				// hard coded here !:o
				upgrade_btn->get_sprite().setTexture(*GlobalShared::get_texture(Constants::UIAssets::tower_2_upgrade_btn));
				SoundManager::play_one_shoot(Constants::TowerAssets::get_tower_build_sound(id));
			}
			//else
			//{
				// make a feedback here it button is not already disabled state
			//}
		}

		bool Tower::is_max_level() const
		{
			return level >= GlobalShared::get_gd().towers.at(id).projectile_params.size()-1;
		}

		TowerId Tower::get_tile_id() const
		{
			return id;
		}

		void Tower::on_game_over()
		{
			if (shoot_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(shoot_time_out_id);
				shoot_time_out_id = 0;
			}
			update_active = false;
			collider->gameobject_enabled = false;
			collider->mouse_enabled = false;
			sprite->setTexture(*Constants::TowerAssets::get_broken_tower_texture(id));
		}

		const ProjectileParams& Tower::get_current_projectile_params() const
		{
			return params.projectile_params.at(level);
		}

		const Texture* Tower::get_current_projectile_texture() const
		{
			assert(level >= 0 && level < params.projectile_params.size());
			return Constants::ProjectileAssets::get_projectile_texture(id, level);
		}

		void Tower::update_range_feeback()
		{
			range_feedback->setPointCount(range_feedback->getPointCount()*2);
			range_feedback->setRadius(calc_collider_circle_radius());
			range_feedback->setPosition(
				-range_feedback->getRadius() + Constants::AssetsConfig::tile_size/2,
				-range_feedback->getRadius() + Constants::AssetsConfig::tile_size/2
			);
			range_feedback->setOutlineColor(Constants::TowerAssets::get_tower_range_feedback(id).first);
			range_feedback->setOutlineThickness(Constants::TowerAssets::get_tower_range_feedback(id).second);
		}
	}
}
