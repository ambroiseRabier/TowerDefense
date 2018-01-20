#pragma once
#include "Castle.hpp"
#include "Tile.hpp"


struct MapParams
{
	// get_size() dépend de map backgorund tile array
	// map background tile array
	// wave_param_array
	// others stuff, like mabiance, music, ...

	/**
	 * \brief 
	 * Fixed size to 28 on x, 21 on y (should be choose according to default screen size and gd).
	 * We could use a vector to make the size variable.
	 */
	const std::array<std::array<TileId,28>, 21> map_background_tile_array;
};

class MapManager
{
public:
	MapManager();
	~MapManager();
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
};

