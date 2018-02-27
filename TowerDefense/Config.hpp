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
			const std::string config_file = "Settings/config.json";
			const std::string game_design_file = "Settings/game_design.json";
			const std::string level_design_file = "Settings/level_design.json";
			const std::string translation_file = "Settings/translation.json";
			const std::string game_name = "Patchwork"; // if you change this, you probably need to change namespaces ;)
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
			const sf::Color collider_debug_color = sf::Color(240,10,15,100);
		}
		
		/**
		 * \brief You should use them as guideline for z-index assignation to gameobjects.
		 * If you ever happen to think you might overlap on another range of z-index, just up max and add a bigger range.
		 */
		namespace ZIndex // use a contexpr with math.max and math.min to check if in range ? use enum ?
		{
			const unsigned int min = 0;
			const unsigned int level_background = 15;
			const unsigned int tile_background = 20;
			const unsigned int minions_dead = 199;
			const unsigned int minions = 200;
			const unsigned int towers = 250;
			const unsigned int projectile = 275;
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