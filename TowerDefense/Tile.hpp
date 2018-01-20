#pragma once
#include "GameEngine/BaseGameObject.hpp"

namespace TowerDefense
{
	namespace Game
	{
		namespace Map
		{
			/**
			 * \brief 
			 * String symbol is gonna be important if we want to export/import it to/from file.
			 * Should be unique to class.
			 * Norm is 
			 * suffix _Walk from minion walkable, 
			 * suffix _Build for "can build tower on it"
			 * suffix _Deco for decoration only.
			 * suffix _Other for other (to not make class name conflict).
			 */
			enum TileId
			{
				/**
				 * \brief Play Castle.
				 */
				Castle_Other,
				/**
				 * \brief Spawn for minions.
				 */
				Spawn_Other,
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
			};

			/**
			 * \brief 
			 * For loading from file. 
			 * (you should use " " column separator and return to line for row separator)
			 * WHY NOT MAKE ENUM CLASS WITH CHAR ? Because I like the possibility of adding more character,
			 * and this is a good exemple of string enum.
			 */
			static std::unordered_map<std::string, TileId> stringToTileIdEnum = {
				{"M", Castle_Other},
				{"@", Spawn_Other},
				{"_", Road_Walk},
				{"o", Grass_Build},
				{"#", Wall_Deco},
				{"i", Grass_Deco},
			};


			class Tile : public TowerDefense::GameEngine::BaseGameObject
			{
			public:
				Tile();
				~Tile();
				const TileId get_tile_id() const;
			private:
				/**
				 * \brief 
				 * Should be unique to the class.
				 */
				TileId id;
			};
		}
	}
}
