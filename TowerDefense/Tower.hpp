#pragma once
#ifndef TOWER_HPP
#define TOWER_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "ProjectileParams.hpp"

namespace TowerDefense
{
	namespace Game
	{
		struct TowerParams;

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
			void on_game_object_overlap(GameObject& game_object) override;
			void update_position();
			TowerId get_tile_id() const;
			const sf::Vector2u map_pos;
		private:
			void shoot() const;
			const ProjectileParams& get_current_projectile_params() const;
			void reset_shoot_delay();
			TowerId id;
			const TowerParams& params;
			GameObject* target;
			unsigned int level=0;
			unsigned int shoot_time_out_id=0;
		};
	}
}
#endif
