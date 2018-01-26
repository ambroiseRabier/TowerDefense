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
			Minion(sf::Vector2u current_tile_pos);
			~Minion();
		protected:
			sf::Sprite* sprite;
			sf::Vector2i current_tile_pos;
			sf::Vector2i next_tile_pos;
			// faire un speed, non clamp � la position, du coup si un gars va trop vite il se d�calera sur le c�t�
			// dans un tournant, l'effet peut �tre sympa et est tol�rable.
			void start() override;
			void update() override;
		};
	}
}
#endif
