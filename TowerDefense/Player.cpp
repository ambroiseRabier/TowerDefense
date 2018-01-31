#include "stdafx.h"
#include "Player.hpp"
#include "Hud.hpp"
#include "Tower.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Player::Player()
		{
		}

		Player::~Player()
		{
			if (tower.get()) tower.reset(nullptr);
		}

		void Player::set_money(const float& value)
		{
			UI::Hud::set_money_text(std::to_string(value));
		}

		void Player::create_tower(const TowerId tower_id)
		{
			// todo: add a switch of towerId
			//tower = std::unique_ptr<Tower>(Tower::create_stone_tower(sf::Vector2u(2,2)));
			//tower->auto_start();
		}

		void Player::on_next_level()
		{
			if (castle) castle = nullptr;
			if (tower.get()) tower.reset(nullptr);
		}

		void Player::assign_castle(Castle* new_castle)
		{
			castle = new_castle;
		}
	}
}
