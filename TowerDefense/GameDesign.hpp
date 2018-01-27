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
			const int game_speed_default_index = 1;
			const float game_speed_choices[4] = {0.5f, 1.0f, 2.0f, 3.0f};
			const std::unordered_map<MinionId, MinionParams> minions = {
				// minion, speed, health, damage, money, life_time
				{Peon, {2.f, 1.f, 2.f, 10.f, 5.f}},
				{Tank, {1.f, 3.f, 6.f, 30.f, 5.f}},
				{Heal, {1.5f, 2.f, 1.f, 50.f, 5.f}},
			};
			const TowerParams cdj ={ // the fuck, compiler say no problem when I add this for towers bellow. Remove this and see...
				{ // intelliSensse problem ?
					{},
				}
			};
			const std::unordered_map<TowerId, TowerParams> towers = {
				{
					StoneTower, 
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
	}
}
#endif