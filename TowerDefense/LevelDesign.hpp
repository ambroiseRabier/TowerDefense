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
				// start money
				50.f,
				// tiles
				{
					{{Grass_Build}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build}, {Grass_Build},},
					{{Grass_Build}, {Road_Walk}, {Grass_Build}, {Road_Walk}, {Grass_Build}, {Grass_Build},},
					{{Spawn_Other}, {Grass_Build}, {Grass_Build}, {Road_Walk}, {Grass_Build}, {Castle_Other},},
					{{Road_Walk}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build}, {Grass_Build},},
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
}
#endif