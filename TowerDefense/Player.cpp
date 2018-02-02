#include "stdafx.h"
#include "Player.hpp"
#include "Hud.hpp"
#include "Tower.hpp"
#include "MapManager.hpp"
#include "Managers/GameManager.hpp"
#include "GameDesign.hpp"

using namespace sf;
namespace TowerDefense
{
	namespace Managers
	{
		Castle* Player::castle;
		std::unique_ptr<Tower> Player::tower;
		float Player::money;
		bool Player::can_set_initial_money_flag;
		Sharp::Event<void> Player::on_money_change;

		void Player::init()
		{
			MapManager::on_destroy_level += Sharp::EventHandler::Bind(&Player::on_destroy_level);
			//GlobalShared::on_window_close += no needed for now.
			can_set_initial_money_flag = true;
		}

		void Player::set_initial_money(const float& value)
		{ 
			assert(can_set_initial_money_flag);
			can_set_initial_money_flag = false;
			set_money(money + value);
		}

		void Player::add_money(const float& value)
		{ 
			assert(value >= 0.f);
			set_money(money + value); // bug: huum, risk that it goes over the size of an float.
		}

		bool Player::can_buy_tower(TowerId tower_id)
		{
			return money - get_tower_cost(tower_id) >= 0.f;
		}

		bool Player::can_upgrade_tower(TowerId tower_id, unsigned int level)
		{
			return money - get_tower_cost(tower_id, level) >= 0.f;
		}

		void Player::buy_tower(TowerId tower_id, const Vector2u& map_pos)
		{
			assert(can_buy_tower(tower_id));
			create_tower(tower_id, map_pos);
			// after creating tower, so tower will display upgrade_btn with updated data.
			set_money(money - get_tower_cost(tower_id));
		}

		float Player::get_tower_cost(TowerId tower_id, unsigned int level)
		{
			return Constants::GameDesign::towers.at(tower_id).projectile_params.at(level).upgrade_cost;
		}

		void Player::set_money(const float& new_value)
		{
			money = std::max(0.f, new_value); // could depass float max value ?
			UI::Hud::set_money_text(std::to_string(money));
			on_money_change();
		}

		void Player::create_tower(const TowerId tower_id, const Vector2u& map_pos)
		{
			switch (tower_id) { 
			case StoneTower: 
				tower = std::unique_ptr<Tower>(Tower::create_stone_tower(map_pos));
				break;
			case FreezeTower: 
				tower = std::unique_ptr<Tower>(Tower::create_freeze_tower(map_pos));
				break;
			case ExplosivTower: 
				tower = std::unique_ptr<Tower>(Tower::create_explosiv_tower(map_pos));
				break;
			}
			tower->auto_start();
		}

		void Player::start()
		{
			buy_tower(TowerId::StoneTower, Vector2u(2,2));
		}

		void Player::set_castle(Castle* new_castle) // could have multiple castle
		{
			assert(new_castle != nullptr);
			castle = new_castle;
			castle->get_health().on_death += Sharp::EventHandler::Bind(&Player::on_castle_death);
		}

		void Player::on_castle_death()
		{
			if (tower)
				tower->on_game_over();
			GameManager::game_over();
		}

		void Player::on_destroy_level()
		{
			if (castle) {
				castle->get_health().on_death -= Sharp::EventHandler::Bind(&Player::on_castle_death);
				castle = nullptr;
			}
			if (tower.get()) tower.reset(nullptr);
			can_set_initial_money_flag = true;
		}
	}
}
