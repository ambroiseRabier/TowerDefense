#pragma once

#ifndef GAME_DESIGN_HPP
#define GAME_DESIGN_HPP
#include "Minion.hpp"
#include "MinionParams.hpp"
#include "TowerParams.hpp"
#include "Tower.hpp"

using namespace TowerDefense::Game;
namespace TowerDefense
{
	namespace Constants
	{
		namespace GameDesign
		{ 
			/**
			 * \brief First value is default.
			 * Update game_speed_pitch_choices in SoundsAssets accordingly.
			 */
			const float game_speed_choices[4] = {1.0f, 2.0f, 3.0f, 0.5f};


			const std::vector<TileId> walkable_tile {
				TileId::Road_Walk,
				TileId::Castle_Other,
			};

			const std::vector<TileId> buildable_tile {
				TileId::Grass_Build
			};

			/**
			 * \brief Life of the castle, minimum is 1.f
			 */
			const float castle_life = 10.f;
			const std::unordered_map<MinionId, MinionParams> minions = {
				// { speed, health, damage, money, heal_others, heal_delay }
				{Peon, {0.5f, 1.f, 2.f, 10.f, 0.f, 0.f}},
				{Tank, {0.25f, 6.f, 6.f, 30.f, 0.f, 0.f}},
				{Heal, {0.333f, 2.f, 1.f, 50.f, 0.02f, 0.1f}},
			};
			
			/**
			 * \brief Score map.
			 */
			const std::unordered_map<MinionId,unsigned int> minion_to_score = {
				{ Peon, 10  },
				{ Tank, 30 },
				{ Heal, 50 },
			};
			const TowerParams cdj ={ // the fuck, compiler say no problem when I add this for towers bellow. Remove this and see...
				{ // intelliSensse problem ?
					{},
				}
			};

			const std::unordered_map<TowerId, TowerParams> towers = { // need a quick tower, and high range tower, huum.
				{
					TowerId::StoneTower, 
					// towerParams
					{
						// projectile params vector
						// first projectile params is also cost of tower itself.
						{
							//projectile params
							// reload_delay, speed, damage, range, freeze_factor, damage_radius, price
							{1.f, 1.f, 1.f, 1.5f, 0.f, 0.f, 50.f},
							{0.75f, 1.25f, 1.f, 2.5f, 0.f, 0.f, 100.f}, // quick and lightweight and quick reload
							{0.5f, 1.5f, 1.f, 3.f, 0.f, 0.f, 150.f}, // even more
						}
					},
				},
				{
					TowerId::FreezeTower,
					{
						{
							{2.f, 0.75f, 0.5f, 1.f, 0.33f, 0.f, 120.f},
							{1.6f, 0.9f, 0.5f, 1.5f, 0.5f, 0.f, 200.f}, // a bit better
							{1.f, 1.f, 0.75f, 2.f, 0.65f, 0.f, 320.f}, // much better
						},
					},
				},
				{
					TowerId::ExplosivTower,
					{
						{
							{1.5f, 1.6f, 0.5f, 2.5f, 0.f, 10.f, 250.f}, // boom
							{2.5f, 1.4f, 0.75f, 3.5f, 0.f, 20.f, 500.f}, // BOOm
							{2.5f, 1.2f, 1.f, 5.5f, 0.f, 30.f, 1000.f}, // BOOOOM
						},
					},
				},
			};
		}
	}
}
#endif