#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Tower.hpp"
#include "Castle.hpp"

using namespace TowerDefense::Game;
namespace TowerDefense
{
	namespace Managers
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
			static void init();
			static void set_initial_money(const float& value);
			static void set_castle(Castle* new_castle);
			/**
			 * \brief When the player can start adding towers.
			 */
			static void start();
		private:
			static void create_tower(const TowerId tower_id, const sf::Vector2u& map_pos);
			static Castle* castle;
			static std::unique_ptr<Tower> tower;
			// Might be hard to make it become part of the map gameplay (minions stealing money)
			static float money;
			static void on_castle_death();
			static void on_destroy_level();
			/**
			 * \brief Assure that initial money is set only one time per map.
			 */
			static bool can_set_initial_money_flag;
		};
	}
}
#endif
