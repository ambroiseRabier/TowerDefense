#pragma once
#ifndef LEVEL_DESIGN_HPP
#define LEVEL_DESIGN_HPP
#include "MapParams.hpp"

using namespace TowerDefense::Game;
namespace TowerDefense
{
	namespace Constants
	{
		namespace LevelDesign
		{

			const MapParams level0 = {
				// name displayed
				"Hello world",
				// preparation time
				3,
				// start money
				50.f,
				// tiles
				{
					{{Moutain_Deco}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Moutain_Deco},},
					{{Moutain_Deco}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build},},
					{{Moutain_Deco}, {Road_Walk}, {Grass_Build}, {Grass_Build}, {Road_Walk}, {Grass_Build},},
					{{Spawn_Other}, {Road_Walk}, {Grass_Build}, {Grass_Build}, {Road_Walk}, {Road_Walk}, {Castle_Other},},
					{{Moutain_Deco}, {Road_Walk}, {Grass_Build}, {Grass_Build}, {Road_Walk}, {Grass_Build},},
					{{Moutain_Deco}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build},},
					{{Moutain_Deco}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Moutain_Deco},},
				},
				// waveParams vector
				{
					// waveParam
					{
						0.0f, // additionnal time before next wave
						{
							{1.f, Heal}, // time before next minon and current minion spawned.
							{2.f, Peon},
							{2.f, Tank},
						},
					},					
					{
						2.0f,
						{
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{0, Peon},
						},
					},
					{
						3.0f,
						{
							{1.f, Tank},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
						},
					},
				}
			};

			const MapParams level1 = {
				// name displayed
				"Last Level !",
				// preparation time
				3,
				// start money
				150.f,
				// tiles
				{
					{{Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco},},
					{{Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco},},
					{{Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco},},
					{{Moutain_Deco}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build},},
					{{Moutain_Deco}, {Moutain_Deco}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build},},
					{{Grass_Build}, {Spawn_Other}, {Road_Walk}, {Grass_Build}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Castle_Other},},
					{{Moutain_Deco}, {Moutain_Deco}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build},},
					{{Moutain_Deco}, {Grass_Build}, {Moutain_Deco}, {Grass_Build}, {Grass_Build}, {Grass_Build},},
					{{Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco},},
					{{Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco},},
					{{Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco}, {Moutain_Deco},},
				},
				// waveParams vector
				{
					// waveParam
					{
						0.0f, // additionnal time before next wave
						{
							{1.f, Heal}, // time before next minon and current minion spawned.
							{2.f, Peon},
							{2.f, Peon},
							{2.f, Peon},
							{2.f, Tank},
						},
					},					
					{
						2.0f,
						{
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Heal},
							{0.f, Peon},
							{0.f, Peon},
							{0.f, Peon},
							{0.f, Peon},
							{1.f, Peon},
							{0, Peon},
						},
					},
					{
						3.0f,
						{
							{1.f, Tank},
							{1.f, Tank},
							{1.f, Tank},
							{0.f, Peon},
							{0.f, Peon},
							{0.f, Peon},
							{0.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
							{1.f, Peon},
						},
					},
				}
			};

			const std::array<MapParams,2> map_array = {
				level0,
				level1
			};

		}
	}
}
#endif