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
			 */
			const float game_speed_choices[4] = {1.0f, 2.0f, 3.0f, 0.5f};

			/**
			 * \brief Life of the castle, minimum is 1.f
			 */
			const float castle_life = 10.f;
			const std::unordered_map<MinionId, MinionParams> minions = {
				// { speed, health, damage, money }
				{Peon, {0.5f, 1.f, 2.f, 10.f}},
				{Tank, {0.25f, 3.f, 6.f, 30.f}},
				{Heal, {0.333f, 2.f, 1.f, 50.f}},
			};
			const TowerParams cdj ={ // the fuck, compiler say no problem when I add this for towers bellow. Remove this and see...
				{ // intelliSensse problem ?
					{},
				}
			};
			const std::unordered_map<TowerId, TowerParams> towers = { // need a quick tower, and high range tower, huum.
				{
					StoneTower, 
					// towerParams
					{
						// projectile params vector
						// first projectile params is also cost of tower itself.
						{
							//projectile params
							// reload_delay, speed, damage, range, freeze_factor, radius_effect, upgrade_cost
							{1.f, 1.f, 1.f, 1.5f, 0.f, 0.f, 50.f},
							{0.75f, 1.5f, 1.f, 2.5f, 0.f, 0.f, 75.f}, // quick and lightweight and quick reload
							{1.5f, 1.f, 2.f, 3.5f, 0.f, 0.f, 100.f}, // slow and heavy and slow reload
						}
					},
				},
				{
					FreezeTower,
					{
						{
							{2.f, 0.5f, 0.5f, 1.f, 0.33f, 0.f, 60.f},
							{1.6f, 0.7f, 0.5f, 1.5f, 0.5f, 0.f, 100.f}, // a bit better
							{1.f, 1.f, 0.75f, 2.f, 0.65f, 0.f, 140.f}, // much better
						},
					},
				},
				{
					ExplosivTower,
					{
						{
							{2.5f, 1.6f, 0.5f, 3.5f, 0.f, 1.f, 110.f}, // boom
							{2.5f, 1.4f, 0.75f, 3.5f, 0.f, 2.f, 220.f}, // BOOm
							{2.5f, 1.2f, 1.f, 5.5f, 0.f, 4.f, 330.f}, // BOOOOM
						},
					},
				},
			};
		}
	}
}
#endif