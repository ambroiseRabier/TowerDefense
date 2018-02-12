#pragma once
#include "MinionParams.hpp"
#include "Minion.hpp"
#include "TowerParams.hpp"
#include "Tower.hpp"

namespace TowerDefense
{
	namespace ExternalConstants
	{
		struct Config
		{
			unsigned int fps_limit = 144;
			unsigned int window_width = 1280;
			unsigned int window_height = 720;
			bool debug_draw_collider = false;
		};

		inline void from_json(const json& j, Config& p) {
			// if one exception occur, multiple settings might use default.
			// solution would be use a try catch for every field.
			try
			{
				p.fps_limit = j.at("fps_limit").get<unsigned int>();
				p.window_width = j.at("window_width").get<unsigned int>();
				p.window_height = j.at("window_height").get<unsigned int>();
				p.debug_draw_collider = j.at("debug_draw_collider").get<bool>();
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}

		struct GameDesign
		{
			/**
			 * \brief First value is default.
			 * Update game_speed_pitch_choices in SoundsAssets accordingly.
			 */
			std::array<float,4> game_speed_choices = {1.0f, 2.0f, 3.0f, 0.5f};

			/**
			 * \brief Life of the castle, minimum is 1.f
			 */
			float castle_life = 10.f;

			std::unordered_map<Game::MinionId, Game::MinionParams> minions = {
				// { speed, health, damage, money, heal_others, heal_delay, score }
				{Game::Peon, {0.5f, 1.f, 2.f, 10.f, 0.f, 0.f, 10.f}},
				{Game::Tank, {0.25f, 6.f, 6.f, 30.f, 0.f, 0.f, 30.f}},
				{Game::Heal, {0.333f, 2.f, 1.f, 50.f, 0.02f, 0.1f, 50.f}},
			};

			std::unordered_map<Game::TowerId, Game::TowerParams> towers = { // need a quick tower, and high range tower, huum.
				{
					Game::TowerId::StoneTower, 
					// towerParams
					{
						// projectile params vector
						// first projectile params is also cost of tower itself.
						{
							//projectile params
							// reload_delay, speed, damage, range, freeze_factor, damage_radius, price
							{1.f, 1.f, 1.f, 1.5f, 0.f, 0.f, 50.f},
							{0.75f, 1.25f, 1.f, 2.5f, 0.f, 0.f, 100.f}, 
							{0.5f, 1.5f, 1.f, 3.f, 0.f, 0.f, 150.f},
						}
					},
				},
				{
					Game::TowerId::FreezeTower,
					{
						{
							{2.f, 0.75f, 0.5f, 1.f, 0.33f, 0.f, 120.f},
							{1.6f, 0.9f, 0.5f, 1.5f, 0.5f, 0.f, 200.f}, 
							{1.f, 1.f, 0.75f, 2.f, 0.65f, 0.f, 320.f},
						},
					},
				},
				{
					Game::TowerId::ExplosivTower,
					{
						{
							{1.5f, 1.6f, 0.5f, 2.5f, 0.f, 10.f, 250.f}, 
							{2.5f, 1.4f, 0.75f, 3.5f, 0.f, 20.f, 500.f}, 
							{2.5f, 1.2f, 1.f, 5.5f, 0.f, 30.f, 1000.f}, 
						},
					},
				},
			};
		};

		inline void from_json(json j, GameDesign& p) {
			// if one exception occur, multiple settings might use default.
			// solution would be use a try catch for every field.
			try
			{
				p.game_speed_choices = j.at("game_speed_choices").get<std::array<float,4>>();
				p.castle_life = j.at("castle_life").get<float>();

				// minions
				auto temp_minions = j.at("minions").get<std::unordered_map<std::string, Game::MinionParams>>();
				for (const auto minion : temp_minions)
				{
					p.minions[Game::stringToMinionIdEnum.at(minion.first)] = minion.second;
				}

				// towers
				auto temp_towers = j.at("towers").get<std::unordered_map<std::string, Game::TowerParams>>();
				for (const auto tower : temp_towers)
				{
					p.towers[Game::stringToTowerIdEnum.at(tower.first)] = tower.second;
				}

				
				// get enum do not vork, l-value of something not blabla
				//auto op = j.at("minions").get<std::unordered_map<Game::MinionId, Game::MinionParams>>(); not ok
				//auto op = j.at("minions").get<std::unordered_map<std::string, Game::MinionParams>>(); ok
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}
	}
}
