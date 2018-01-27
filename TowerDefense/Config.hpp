#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

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
			const float min_loading_duration = 2.0f;
			/**
			 * \brief 
			 * Assigned at start to Physics::testedCollisions.
			 * Collision are one way (pair.first get the event of the collision)
			 */
			const std::vector<std::pair<Collider::Tag, Collider::Tag>> tested_collisions = {
				std::make_pair(Collider::Tag::Minion, Collider::Tag::Castle),
				std::make_pair(Collider::Tag::Projectile, Collider::Tag::Minion),
				std::make_pair(Collider::Tag::Tower, Collider::Tag::Minion),
			};
			const unsigned int window_width = 1280;
			const unsigned int window_height = 720;
			const bool debug_draw_collider = true;
			const sf::Color collider_debug_color = sf::Color(240,10,15,100);
		}
		
		/**
		 * \brief You should use them as guideline for z-index assignation to gameobjects.
		 * If you ever happen to think you might overlap on another range of z-index, just up max and add a bigger range.
		 */
		namespace ZIndex // use a contexpr with math.max and math.min to check if in range ? use enum ?
		{
			const unsigned int background_start = 0;
			const unsigned int tile_background = 20;
			const unsigned int towers = 50;
			const unsigned int projectile = 75;
			const unsigned int game_objects_start = 100;
			const unsigned int minions_start = 200;
			const unsigned int hpBars_background_start = 300;
			const unsigned int hpBars_jauge_start = 301;
			const unsigned int ui_start = 900;
			const unsigned int max = 999;
		}
	}
}
#endif