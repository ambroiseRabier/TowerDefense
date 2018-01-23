#pragma once
#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP
#include "Castle.hpp"
#include "MapParams.hpp"
#include "Spawn.hpp"
using namespace TowerDefense::Game;
namespace TowerDefense
{
	namespace Managers
	{
		/**
		 * \brief 
		 * Handle map loading and destroying.
		 */
		class MapManager
		{
		public:
			/**
			 * \brief Intended for use of Player only. (A better design would be dependancy injection I guess)
			 * \return Castle.
			 */
			static Castle& get_castle();
			static void init();
			/**
			 * \brief 
			 * Generate Level according to Config.
			 * Destroy current level if not already done.
			 * \param level_number 
			 */
			static void load_level(const unsigned int& level_number);
			/**
			 * \brief 
			 * Destroy current level.
			 */
			static void destroy_current_level();
			static const MapParams* map_params;
			static const bool get_level_loaded_flag();
		private:
			static std::shared_ptr<Castle> castle;
			static std::shared_ptr<Spawn> spawn;
			static bool level_loaded_flag;
			static void load_level_internal(const unsigned int& level_number);
			static void create_tiles(const MapParams l_map_params);
			static std::shared_ptr<Tile> spawn_tile(const TileId tile_id);
			static std::map<int, std::map<int, std::shared_ptr<Tile>>> all_tiles;
		};
	}
}
#endif
