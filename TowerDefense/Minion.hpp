#pragma once
#ifndef MINION_HPP
#define MINION_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "Utils/Event.h"
#include "Health.hpp"

namespace TowerDefense
{
	namespace Game
	{
		struct MinionParams;

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
			static Minion* create_peon(const sf::Vector2u& map_pos);
			static Minion* create_tank(const sf::Vector2u& map_pos);
			static Minion* create_heal(const sf::Vector2u& map_pos);
			Minion();
			Minion(sf::Vector2u map_pos, const MinionId minion_id);
			virtual ~Minion();
			Health& get_health() const;
			void init() override;
			void on_game_object_overlap(GameObject& game_object) override;
			void freeze(const float& new_freeze_factor);

		protected:
			const MinionId id;
			sf::Sprite* sprite;
			sf::Vector2u map_pos;
			sf::Vector2u next_map_pos;
			/**
			 * \brief Usefull to avoid returning on previous tile.
			 */
			sf::Vector2u previous_map_pos;
			const MinionParams& params;
			std::unique_ptr<Health> health;
			unsigned int death_time_out_id;
			float freeze_factor = 0.f;
			void on_death();
			void destroy_self();

			// faire un speed, non clamp à la position, du coup si un gars va trop vite il se décalera sur le côté
			// dans un tournant, l'effet peut être sympa et est tolérable.
			void start() override;
			void update() override;
			void update_move();

			/**
			 * \brief 
			 * \return Minion speed at this frame.
			 */
			float calc_speed() const;


			/**
			 * \brief Same as calc_position, but no degree or radian here................
			 * \param target_pos 
			 * \param speed 
			 * \return 
			 */
			sf::Vector2f calc_pos(const sf::Vector2f& target_pos, const float& speed) const;

			/**
			 * \brief Calculate next position based on rotation of the transform and given speed.
			 * \param rotation Degree
			 * \param speed 
			 * \return 
			 */
			sf::Vector2f calc_position(const float& rotation, const float& speed) const;

			/**
			 * \brief Calculate rotation to face a given position.
			 * \param rotateTo Degree
			 * \return Degree
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
			bool validate_pos(const sf::Vector2u& new_pos) const;
		};
	}
}
#endif
