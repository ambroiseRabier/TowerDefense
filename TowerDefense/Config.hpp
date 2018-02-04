#pragma once
#ifndef CONFIG_HPP
#define CONFIG_HPP
#include "Minion.hpp"
#include "Phantom.hpp"

using namespace TowerDefense::GameEngine;
namespace TowerDefense
{
	namespace Constants
	{
		
		/**
		 * \brief Config for the game.
		 */
		namespace Config
		{
			const std::string game_name = "TowerDefense"; // if you change this, you probably need to change namespaces ;)
			const unsigned int fps_limit = 30;
			/**
			 * \brief 
			 * Assigned at start to CollisionManager::testedCollisions.
			 * Collision are one way (pair.first get the event of the collision)
			 * It read 'first' collid with 'second', 'first' get the collision event.
			 */
			const std::vector<std::pair<Collider::Tag, Collider::Tag>> tested_collisions = {
				std::make_pair(Collider::Tag::Minion, Collider::Tag::Castle),
				std::make_pair(Collider::Tag::HealMinion, Collider::Tag::Castle),
				std::make_pair(Collider::Tag::Projectile, Collider::Tag::Minion),
				std::make_pair(Collider::Tag::Projectile, Collider::Tag::HealMinion),
				std::make_pair(Collider::Tag::Tower, Collider::Tag::Minion),
				std::make_pair(Collider::Tag::Tower, Collider::Tag::HealMinion),
				std::make_pair(Collider::Tag::HealMinion, Collider::Tag::HealMinion),
				std::make_pair(Collider::Tag::HealMinion, Collider::Tag::Minion),
			};
			const unsigned int window_width = 1280;
			const unsigned int window_height = 720;
			const bool debug_draw_collider = true;
			const sf::Color collider_debug_color = sf::Color(240,10,15,100);
			const std::string final_wave_text = "Last wave !";
			const std::string wave_number_text = "Wave";
			const std::string win_screen_text = "You saved the castle !";
			const std::string game_over_screen_text = "The castle has been lost !";
			const std::string pause_text = "Pause";
			const std::string game_cleared_text = "Game Cleared !";
			const std::string help_tower_build_text = "Left->build   Right->cancel";
		}
		
		/**
		 * \brief You should use them as guideline for z-index assignation to gameobjects.
		 * If you ever happen to think you might overlap on another range of z-index, just up max and add a bigger range.
		 */
		namespace ZIndex // use a contexpr with math.max and math.min to check if in range ? use enum ?
		{
			const unsigned int min = 0;
			const unsigned int tile_background = 20;
			const unsigned int minions_dead = 199;
			const unsigned int minions = 200;
			const unsigned int projectile = 250;
			const unsigned int towers = 275;
			const unsigned int hpBars_jauge = 301;
			const unsigned int tower_upgrade_btn = 350;
			const unsigned int phantom_tower = 400;
			const unsigned int ui_background = 899;
			const unsigned int ui = 900;
			const unsigned int max = 999;
		}
	}
}
#endif