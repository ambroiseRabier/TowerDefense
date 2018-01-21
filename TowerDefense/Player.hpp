#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace TowerDefense
{
	namespace Game
	{
		/**
		 * \brief 
		 * Handle Castle, HUD.
		 * Would be best handled as instance instead of manager, make it easier to restart game from 0.
		 * Shoulb be created when the game start by GameManager, and destroyed when game end (return to menu). Should contain info for hud.
		 * use HUD
		 * use MapManager::get_castle()
		 */
		class Player
		{
		public:
			Player();
			~Player();
			void set_money(const float& value);
		};
	}
}
#endif
