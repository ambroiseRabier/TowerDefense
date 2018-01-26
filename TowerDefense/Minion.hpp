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
			Minion(sf::Vector2u map_pos);
			~Minion();
		protected:
			sf::Sprite* sprite;
			sf::Vector2u map_pos;
			sf::Vector2u next_map_pos;
			// faire un speed, non clamp à la position, du coup si un gars va trop vite il se décalera sur le côté
			// dans un tournant, l'effet peut être sympa et est tolérable.
			void start() override;
			void update() override;

			/**
			 * \brief Calculate next position based on rotation of the transform and given speed.
			 * \param rotation 
			 * \param speed 
			 * \return 
			 */
			sf::Vector2f calc_position(const float& rotation, const float& speed) const;

			/**
			 * \brief Calculate rotation to face a given position.
			 * \param rotateTo 
			 * \return 
			 */
			float calc_rotation(const sf::Vector2f& rotateTo) const;

			/**
			 * \brief 
			 * Find the next map position.
			 * \param current_map_pos 
			 * \return 
			 * Then ext map position, if none found it return the map position passed in parameter.
			 */
			sf::Vector2u find_next_map_pos(const sf::Vector2u& current_map_pos) const;
		};
	}
}
#endif
