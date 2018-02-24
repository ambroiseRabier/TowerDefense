#pragma once
#ifndef TILE_ASSETS_HPP
#define TILE_ASSETS_HPP
#include "Tile.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace Constants
	{
		namespace TileAssets
		{
			const std::string castle_others = "Assets/Tile/castle_negated.png";
			const std::string spawn_others = "Assets/Tile/spawn.png";
			const std::string road_walk = "Assets/Tile/road.png";
			const std::string grass_build = "Assets/Tile/grass.png";
			const std::string moutain_deco = "Assets/Tile/moutain_deco.png";
			const std::string castle_death = "Assets/Tile/castle_negated_destroyed.png";
			const std::string transparent_deco = "Assets/Tile/transparent.png";

			const std::unordered_map<Game::TileId, std::string> tile_id_map {
				{Game::TileId::Castle_Other, castle_others},
				{Game::TileId::Spawn_Other, spawn_others},
				{Game::TileId::Road_Walk, road_walk},
				{Game::TileId::Grass_Build, grass_build},
				{Game::TileId::Wall_Deco, grass_build},
				{Game::TileId::Moutain_Deco, moutain_deco},
				{Game::TileId::Transparent_Deco, transparent_deco},
			};

			inline sf::Texture* get_tile_texture(Game::TileId tile_id)
			{
				return GlobalShared::get_texture(tile_id_map.at(tile_id));
			}
		}
	}
}
#endif

