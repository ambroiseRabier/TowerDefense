#include "stdafx.h"
#include "Player.hpp"
#include "HUD.hpp"
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
			UI::HUD::set_money_text(std::to_string(value));
		}

		void Player::create_tower(const TowerId tower_id)
		{
			// add a switch of towerId
			tower = std::unique_ptr<Tower>(Tower::create_stone_tower(sf::Vector2u(2,2)));
			//Tower* temp = Tower::create_stone_tower(sf::Vector2u(2,2));
			//tower = std::make_unique<Tower>(*temp);
			tower->auto_start();
		}
	}
}
