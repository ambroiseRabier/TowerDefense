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
			static void on_game_over();
			static void on_game_win();

			/**
			* \brief For Screens to display the score.
			*/
			static const int& get_score();
			static void add_score(const unsigned int& add_value);
			/**
			 * \brief Case when player lose his score, for KISS reason we do it this way.
			 * Player lose score in two cases:
			 * - Leave game_over state. (screen)
			 * - return to menu.
			 * - leave game_cleared state. (screen)
			 * A win do not reset the score, this is to promote playing the game from A to Z level.
			 * (make sense with a level selection)
			 */
			static void lose_score();

		private:
			static std::unique_ptr<Phantom> phantom;
			static void create_tower(const TowerId tower_id, const sf::Vector2u& map_pos);
			static Castle* castle;
			static std::vector<std::unique_ptr<Tower>> tower_vector;
			static int score;
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
			static void set_score(const unsigned int& new_score);
		};
	}
}
#endif
