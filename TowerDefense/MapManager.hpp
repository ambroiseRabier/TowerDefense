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
			static Spawn& get_spawn();
			static void init();
			/**
			 * \brief 
			 * Generate Level according to Config.
			 * Destroy current level if not already done.
			 * \param new_map_params
			 */
			static void load_level(const MapParams& new_map_params);
			/**
			 * \brief 
			 * Destroy current level.
			 */
			static void destroy_current_level();
			static bool map_pos_exist(const sf::Vector2u map_pos);
			static bool map_pos_exist(const sf::Vector2i map_pos);
			static bool map_pos_walkable(const sf::Vector2u& map_pos);
			static bool map_pos_walkable(const sf::Vector2i& map_pos);
			static bool map_pos_buildable(const sf::Vector2u& map_pos);
			static bool map_pos_buildable(const sf::Vector2i& map_pos);
			static sf::Vector2i point_to_map_pos(const sf::Vector2i& mouse_position);
			static const MapParams* map_params;
			static const bool get_level_loaded_flag();
			static const sf::Transformable& get_map_origin();
			static Sharp::Event<void> on_destroy_level;
		private:
			static sf::Transformable map_origin;
			static std::unique_ptr<GameEngine::GameObject> background;
			static Castle* castle;
			static Spawn* spawn;
			static bool level_loaded_flag;
			static void load_level_internal(const MapParams& new_map_params);
			static void align_center_map(const MapParams l_map_params);
			static void create_tiles(const MapParams l_map_params);
			//static std::shared_ptr<Tile> spawn_tile(const TileId tile_id);
			static Tile* spawn_tile(const TileId tile_id,  const sf::Vector2u& map_pos);
			static bool compare_row_size_p(const std::vector<TileId> first, const std::vector<TileId> second);
			//static Tile* spawn_tile(const TileId tile_id);
			//static std::map<int, std::map<int, std::shared_ptr<Tile>*>> all_tiles;
			static std::map<unsigned int, std::map<unsigned int, Tile*>> all_tiles_p;
		};
	}
}
#endif
