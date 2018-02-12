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
			const std::vector<TileId> walkable_tile {
				TileId::Road_Walk,
				TileId::Castle_Other,
			};

			const std::vector<TileId> buildable_tile {
				TileId::Grass_Build
			};
			
			const TowerParams cdj ={ // the fuck, compiler say no problem when I add this for towers bellow. Remove this and see...
				{ // intelliSensse problem ?
					{},
				}
			};
		}
	}
}
#endif