#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Tower.hpp"
#include "Castle.hpp"

namespace TowerDefense
{
	namespace Game
	{
		/**
		 * \brief 
		 * Handle Castle, Hud.
		 * Would be best handled as instance instead of manager, make it easier to restart game from 0.
		 * Should contain info for hud.
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
			void assign_castle(Castle* new_castle);
		private:
			Castle* castle;
			std::unique_ptr<Tower> tower;
			// Might be hard to make it become part of the map gameplay (minions stealing money)
			float money;
		};
	}
}
#endif
