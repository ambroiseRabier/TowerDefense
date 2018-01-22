#include "stdafx.h"
#include "Player.hpp"
#include "HUD.hpp"

namespace TowerDefense
{
	namespace Game
	{
		Player::Player()
		{
		}


		Player::~Player()
		{
		}

		void Player::set_money(const float& value)
		{
			UI::HUD::set_money_text(std::to_string(value));
		}
	}
}
