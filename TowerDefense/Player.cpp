#include "stdafx.h"
#include "Player.hpp"
#include "Hud.hpp"
#include "Tower.hpp"
#include "MapManager.hpp"
#include "Managers/GameManager.hpp"

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

		void Player::create_tower(const TowerId tower_id)
		{
			// todo: add a switch of towerId
			tower = std::unique_ptr<Tower>(Tower::create_stone_tower(sf::Vector2u(2,2)));
			tower->auto_start();
		}

		void Player::start()
		{
			//create_tower(TowerId::StoneTower);
		}

		void Player::set_castle(Castle* new_castle)
		{
			assert(new_castle != nullptr);
			castle = new_castle;
		}

		void Player::on_destroy_level()
		{
			if (castle) castle = nullptr;
			if (tower.get()) tower.reset(nullptr);
			can_set_initial_money_flag = true;
		}
	}
}
