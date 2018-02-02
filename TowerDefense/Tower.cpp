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
#include "CastUtils.hpp"
#include "GameObjects/BaseButton.hpp"
#include "Player.hpp"

using namespace TowerDefense::GameEngine;
using namespace sf;
namespace TowerDefense
{
	namespace Game
	{
		Tower* Tower::create_stone_tower(const Vector2u& map_pos)
		{
			return new Tower(
				GlobalShared::stone_tower_texture,
				StoneTower,
				map_pos
			);
		}

		Tower* Tower::create_freeze_tower(const Vector2u& map_pos)
		{
			return new Tower(
				GlobalShared::freeze_tower_texture,
				FreezeTower,
				map_pos
			);
		}

		Tower* Tower::create_explosiv_tower(const Vector2u& map_pos)
		{
			return new Tower(
				GlobalShared::explosiv_tower_texture,
				ExplosivTower,
				map_pos
			);
		}

		Tower::Tower() : params(Constants::GameDesign::towers.at(StoneTower))
		{
			Debug::warn("Tower: default constructor should not be used.");
		}

		Tower::Tower(const Texture* texture, TowerId id, const Vector2u map_pos) 
					: map_pos(map_pos), id(id), params(Constants::GameDesign::towers.at(id))
		{
			auto temp_sprite = std::make_unique<Sprite>(*texture);
			sprite = temp_sprite.get();
			set_drawable(static_cast_ptr<Drawable>(
				temp_sprite
			));
			z_index = Constants::ZIndex::towers;
			collider = std::make_shared<Collider>(
				Circle(
					calc_collider_circle_radius(),
					Constants::AssetsConfig::tile_size_half_vec // box in the center of tile.
				),
				Collider::Tag::Tower
			);
			upgrade_btn = std::make_unique<UI::BaseButton>(
				GlobalShared::tower_1_upgrade_btn_texture,
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
			upgrade_btn->isActive = Managers::Player::can_upgrade_tower(id, level) && !is_max_level(); 
		}

		void Tower::shoot() const 
		{
			// if target has become null in meantime don't shoot. 
			// (destroyed by another tower or out of range, or died on castle)
			// use weak_ptr instead ? because I think it's gonna bug
			if (target == nullptr) 
				return;

			Projectile* proj = new Projectile(
				get_current_projectile_texture(), 
				get_current_projectile_params(),
				transformable->getPosition() + Constants::AssetsConfig::tile_size_half_vec, // could be position of canon
				target->get_transformable().getPosition() + Constants::AssetsConfig::tile_size_half_vec
			);
			proj->auto_start();
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
			return std::max(0.5f, params.projectile_params.at(level).range) * Constants::AssetsConfig::tile_size;
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
				collider->set_circle(
					Constants::AssetsConfig::tile_size_half_vec,
					calc_collider_circle_radius()
				);
				// hard coded here !:o
				upgrade_btn->get_sprite().setTexture(*GlobalShared::tower_2_upgrade_btn_texture);
			}
			//else
			//{
				// make a feedback here it button is not already disabled state
			//}
		}

		bool Tower::is_max_level() const
		{
			return level >= Constants::GameDesign::towers.at(id).projectile_params.size()-1;
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
			switch (id)
			{
			case StoneTower: 
				sprite->setTexture(*GlobalShared::stone_tower_broken_texture);
				break;
			case FreezeTower: 
				sprite->setTexture(*GlobalShared::freeze_tower_broken_texture);
				break;
			case ExplosivTower: 
				sprite->setTexture(*GlobalShared::explosiv_tower_broken_texture);
				break;
			default: ;
			}
		}

		const ProjectileParams& Tower::get_current_projectile_params() const
		{
			return params.projectile_params.at(level);
		}

		const Texture* Tower::get_current_projectile_texture() const
		{
			//todo: maybe inheritance to detemine texture used... ?
			assert(level >= 0 && level < params.projectile_params.size());
			switch (id)
			{
			case StoneTower:
				 return (std::vector<Texture*>{
					GlobalShared::stone_projectile_0_texture,
					GlobalShared::stone_projectile_0_texture,
					GlobalShared::stone_projectile_0_texture
				 }).at(level);
			case FreezeTower: 
				 return (std::vector<Texture*>{
					GlobalShared::freeze_projectile_0_texture,
					GlobalShared::freeze_projectile_0_texture,
					GlobalShared::freeze_projectile_0_texture
				 }).at(level);
			case ExplosivTower: 
				 return (std::vector<Texture*>{
					GlobalShared::explosiv_projectile_0_texture,
					GlobalShared::explosiv_projectile_0_texture,
					GlobalShared::explosiv_projectile_0_texture
				 }).at(level);
			default: ;
			}
			Debug::warn("Tower: missing texture for Tower projectile.");
			return GlobalShared::missing_texture_tile_texture;
		}
	}
}
