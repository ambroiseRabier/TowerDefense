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
				"HelloWorld",
				// start money
				50.f,
				// tiles
				{
					{{Grass_Build}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build}, {Grass_Build},},
					{{Grass_Build}, {Road_Walk}, {Grass_Build}, {Road_Walk}, {Grass_Build}, {Grass_Build},},
					{{Spawn_Other}, {Grass_Build}, {Grass_Build}, {Road_Walk}, {Road_Walk}, {Castle_Other},},
					{{Road_Walk}, {Road_Walk}, {Road_Walk}, {Road_Walk}, {Grass_Build}, {Grass_Build},},
					{{Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build}, {Grass_Build},},
				},
				// waveParams vector
				{
					// waveParam
					{
						3.0f, // time before next wave
						{
							{1.f, Peon}, // time before next minon and current minion spawned.
							{0.5f, Peon},
							{0.5f, Peon},
							{0, Peon},
						},
					},					
					{
						3.0f,
						{
							{1.f, Tank},
							{1.f, Peon},
							{1.f, Tank},
							{0, Peon},
						},
					},
				}
			};

			const std::array<MapParams,1> map_array = {
				level0
			};

		}
	}
}
#endif