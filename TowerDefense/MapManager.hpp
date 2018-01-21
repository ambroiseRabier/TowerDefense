#pragma once
#ifndef MAP_MANAGER_HPP
#define MAP_MANAGER_HPP
#include "Castle.hpp"
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
		private:
			static std::unique_ptr<Castle> castle;
			static bool level_loaded_flag;
			static void load_level_internal(const unsigned int& level_number);
			static void spawn_tile(TileId tile_id);
		};
	}
}
#endif
