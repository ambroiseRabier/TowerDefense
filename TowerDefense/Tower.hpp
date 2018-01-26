#pragma once
#ifndef TOWER_HPP
#define TOWER_HPP
#include "GameEngine/BaseGameObject.hpp"

namespace TowerDefense
{
	namespace Game
	{
		/**
		* \brief 
		* Enum representing the tower type, should be unique to class.
		*/
		enum TowerId
		{
			StoneTower,
			FreezeTower,
			ExplosivTower,
		};

		/**
		 * \brief 
		 * Can only be placed on BuildableTile.
		 */
		class Tower : public GameEngine::BaseGameObject
		{
		public:
			static Tower* create_stone_tower(const sf::Vector2u& map_pos);
			Tower();
			Tower(const sf::Texture* texture, TowerId id, const sf::Vector2u map_pos);
			~Tower();
			void init() override;
			void update_position();
			TowerId get_tile_id() const;
			const sf::Vector2u map_pos;
		protected:
			TowerId id;
		};
	}
}
#endif
