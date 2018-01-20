#pragma once
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include "GameEngine/Collider.hpp"
#include "../MapManager.hpp"
#include "../MapParams.hpp"
#include "../MinionParams.hpp"
#include "../TowerParams.hpp"
#include "../Tower.hpp"
using namespace TowerDefense::GameEngine;
using namespace TowerDefense::Game::Map;
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
			const unsigned int fps_limit = 144;
			const float min_loading_duration = 2.0f;
			/**
			 * \brief Assigned at start to Physics::testedCollisions.
			 */
			const std::vector<std::pair<Collider::Tag, Collider::Tag>> tested_collisions = {
				std::make_pair(Collider::Tag::Minion, Collider::Tag::Castle),
				std::make_pair(Collider::Tag::Minion, Collider::Tag::TowerShoot),
				std::make_pair(Collider::Tag::UI, Collider::Tag::UI) // for demo only !
			};
		}

		/**
		 * \brief Path of the assets (images, sounds, ...)
		 */
		namespace Assets
		{
			const std::string loading_background = "Assets/loading_background_inverted.png";
			const std::string menu_background = "Assets/menu_background.jpg";
			const std::string default_ui_btn = "Assets/orange_btn.jpg";
			const std::string default_font = "Assets/Inconsolata-Regular.ttf";
		}

		/**
		 * \brief You should use them as guideline for z-index assignation to gameobjects.
		 * If you ever happen to think you might overlap on another range of z-index, just up max and add a bigger range.
		 */
		namespace ZIndex // use a contexpr with math.max and math.min to check if in range ? use enum ?
		{
			const unsigned int background_start = 0;
			const unsigned int game_objects_start = 100;
			const unsigned int ui_start = 900;
			const unsigned int max = 999;
		}

		namespace GameDesign
		{ 
			const int game_speed_default_index = 1;
			const float game_speed_choices[4] = {0.5f, 1.0f, 2.0f, 3.0f};
			const std::unordered_map<MinionId, MinionParams> minions = {
				// minion, speed, health, damage, money
				{Peon, {2.f, 1.f, 2.f, 10.f}},
				{Tank, {1.f, 3.f, 6.f, 30.f}},
				{Heal, {1.5f, 2.f, 1.f, 50.f}},
			};
			const TowerParams cdj ={ // the fuck, compiler say no problem when I add this for towers bellow. Remove this and see...
				{ // intelliSensse problem ?
					{},
				}
			};
			const std::unordered_map<TowerId, TowerParams> towers = {
				{
					RockTower, 
					// towerParams
					{
						// projectile params vector
						// first projectile params is also cost of tower itself.
						{
							//projectile params
							// reload_delay, speed, damage, range, freeze_factor, radius_effect, upgrade_cost
							{1.f, 1.f, 1.f, 10.f, 0.f, 0.f, 50.f},
							{0.75f, 1.5f, 1.f, 15.f, 0.f, 0.f, 75.f}, // quick and lightweight and quick reload
							{1.5f, 1.f, 2.f, 20.f, 0.f, 0.f, 100.f}, // slow and heavy and slow reload
						}
					},
				},
				{
					FreezeTower,
					{
						{
							{2.f, 0.5f, 0.5f, 8.f, 0.33f, 0.f, 60.f},
							{1.6f, 0.7f, 0.5f, 12.f, 0.5f, 0.f, 100.f}, // a bit better
							{1.f, 1.f, 0.75f, 16.f, 0.65f, 0.f, 140.f}, // much better
						},
					},
				},
				{
					ExplosivTower,
					{
						{
							{2.5f, 1.6f, 0.5f, 13.f, 0.f, 1.f, 110.f}, // boom
							{2.5f, 1.4f, 0.75f, 17.f, 0.f, 2.f, 220.f}, // BOOm
							{2.5f, 1.2f, 1.f, 21.f, 0.f, 4.f, 330.f}, // BOOOOM
						},
					},
				},
			};
		}

		namespace LevelDesign
		{
			const MapParams level0 = {
				// start money
				50.f,
				// tiles
				{
					{{Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build},},
					{{Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build},},
					{{Spawn_Other}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Castle_Other},},
					{{Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build},},
					{{Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build},},
				},
				// waveParams vector
				{
					// waveParam
					{
						10.0f, // time before next wave
						{
							{1.f, Peon}, // time before next minon and current minion spawned.
							{1.f, Peon},
							{1.f, Peon},
							{0, Peon},
						},
					},					
					{
						20.0f,
						{
							{1.f, Tank},
							{3.f, Peon},
							{1.f, Tank},
							{0, Peon},
						},
					},
				}
			};
		}
	}
	/**
	 * \brief Texture, font, and other assets reference that I need trough the game many times, or that I want to preload.
	 * Guaranted to be setted at main before the Managers init.
	 */
	namespace GlobalShared
	{
		extern sf::Texture* menu_background;
		extern sf::Texture* default_ui_btn;
		extern sf::Font* default_font;
	}
}
#endif

