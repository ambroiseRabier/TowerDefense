#include "stdafx.h"
#include "Player.hpp"
#include "Hud.hpp"
#include "Tower.hpp"
#include "MapManager.hpp"
#include "Managers/GameManager.hpp"

using namespace sf;
namespace TowerDefense
{
	namespace Managers
	{
		Castle* Player::castle;
		std::unique_ptr<Tower> Player::tower;
		float Player::money;
		bool Player::can_set_initial_money_flag;

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
			money = std::max(0.f,value);
			UI::Hud::set_money_text(std::to_string(value));
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
			default: ;
			}
			tower->auto_start();
		}

		void Player::start()
		{
			create_tower(TowerId::FreezeTower, Vector2u(2,2));
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
