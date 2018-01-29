#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Tower.hpp"

namespace TowerDefense
{
	namespace Game
	{
		/**
		 * \brief 
		 * Handle Castle, Hud.
		 * Would be best handled as instance instead of manager, make it easier to restart game from 0.
		 * Shoulb be created when the game start by GameManager, and destroyed when game end (return to menu). Should contain info for hud.
		 * use Hud
		 * use MapManager::get_castle()
		 */
		class Player
		{
		public:
			Player();
			~Player();
			void set_money(const float& value);
			void create_tower(const TowerId tower_id);
			/**
			 * \brief When the level change or restart. But the player is already instanciated.
			 */
			void on_next_level();
		private:
			std::unique_ptr<Tower> tower;
		};
	}
}
#endif
