#pragma once
#ifndef MINION_HPP
#define MINION_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "Utils/Event.h"

namespace TowerDefense
{
	namespace Game
	{
		/**
		 * \brief 
		 * Enum representing the minion type, should be unique to class.
		 */
		enum MinionId
		{
			Peon,
			Tank,
			Heal,
		};

		/**
		 * \brief 
		 * For loading from file.
		 * (you should use " " column separator)
		 */
		static std::unordered_map<std::string, MinionId> stringToMinionIdEnum = {
			{"Peon", Peon}, {"P", Peon},
			{"Tank", Tank}, {"T", Tank},
			{"Heal", Heal}, {"H", Heal},
		};

		class Minion : public  GameEngine::BaseGameObject
		{
		public:
			Minion();
			~Minion();
		protected:
			/*const std::vector<std::vector<TileId>> map_background_tile_array = {
				{ { Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build }, },
				{ { Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build }, },
				{ { Spawn_Other },{ Road_Walk },{ Road_Walk },{ Road_Walk },{ Road_Walk },{ Castle_Other }, },
				{ { Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build }, },
				{ { Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build },{ Grass_Build }, },
			};*/
			sf::Sprite* sprite;
		};
	}
}
#endif
