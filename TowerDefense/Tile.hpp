#pragma once
#include "GameEngine/BaseGameObject.hpp"
#include <unordered_map>


/**
 * \brief 
 * String symbol is gonna be important if we want to export/import it to/from file.
 * Norm is 
 * suffix _Walk from minion walkable, 
 * suffix _Build for "can build tower on it"
 * suffix _Deco for decoration only.
 */
enum TileId
{
	/**
	 * \brief Minions accesible.
	 */
	Road_Walk,
	/**
	 * \brief Can build tower on this grass.
	 */
	Grass_Build,
	/**
	 * \brief Decoration wall.
	 */
	Wall_Deco,
	/**
	 * \brief Decoration grass;
	 */
	Grass_Deco,
} ;

/**
 * \brief 
 * For loading from file. 
 * (you should use " " column separator and return to line for row separator)
 * WHY NOT MAKE ENUM CLASS WITH CHAR ? Because I like the possibility of adding more character,
 * and this is a good exemple of string enum.
 */
static std::unordered_map<std::string, TileId> stringToEnum = {
	{"_", Road_Walk},
	{"o", Grass_Build},
	{"#", Wall_Deco},
	{"i", Grass_Deco},
};


class Tile: public TowerDefense::GameEngine::BaseGameObject
{
public:
	Tile();
	~Tile();
	const TileId get_tile_id();
private:
	/**
	 * \brief 
	 * Should be unique to the class.
	 */
	TileId id;
};

