#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Tower.hpp"
#include "Castle.hpp"
#include "Phantom.hpp"

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
			static Sharp::Event<void> on_money_change;
			static void init();
			static void set_initial_money(const float& value);
			static void add_money(const float& value);
			/**
			 * \brief 
			 * \param tower_id
			 * \return if the tower can has been purchased
			 */
			static bool can_buy_tower(TowerId tower_id);
			static bool can_upgrade_tower(TowerId tower_id, const unsigned int level);
			/**
			 * \brief Buy a tower for you and place it where you need it.
			 * \param tower_id 
			 * \param map_pos 
			 */
			static void buy_tower(TowerId tower_id, const sf::Vector2u& map_pos);
			static void buy_tower_upgrade(TowerId tower_id, const unsigned int level);
			static float get_tower_price(TowerId tower_id, const unsigned int level=0);
			static void set_castle(Castle* new_castle);
			/**
			 * \brief When the player can start adding towers.
			 */
			static void start();
			static void create_phantom_tower(TowerId tower_id);
		private:
			static std::unique_ptr<Phantom> phantom;
			static void create_tower(const TowerId tower_id, const sf::Vector2u& map_pos);
			static Castle* castle;
			static std::vector<std::unique_ptr<Tower>> tower_vector;
			// Might be hard to make it become part of the map gameplay (minions stealing money)
			static float money;
			static void on_castle_death();
			static void on_destroy_level();
			static void on_click_phantom();
			static void on_click_cancel_phantom();
			/**
			 * \brief Use this to change money value, it update HUD and send an event for upgrade btns.
			 * \param new_value 
			 */
			static void set_money(const float& new_value);
			/**
			 * \brief Assure that initial money is set only one time per map.
			 */
			static bool can_set_initial_money_flag;
		};
	}
}
#endif
