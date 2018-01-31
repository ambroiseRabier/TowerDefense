#pragma once
#ifndef TOWER_HPP
#define TOWER_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "ProjectileParams.hpp"

using namespace sf;
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
			static Tower* create_stone_tower(const Vector2u& map_pos);
			Tower();
			Tower(const Texture* texture, TowerId id, const Vector2u map_pos);
			~Tower();
			void init() override;
			void on_game_object_overlap(GameObject& game_object) override;
			void update_position();
			TowerId get_tile_id() const;
			void on_game_over();
			const Vector2u map_pos;
		private:
			void shoot() const;
			const ProjectileParams& get_current_projectile_params() const;
			void reset_shoot_delay();
			void on_projectile_kill();
			/**
			 * \brief Garanted to be valid until tower descontructor.
			 */
			Sprite* sprite;
			TowerId id;
			const TowerParams& params;
			GameObject* target;
			unsigned int level=0;
			unsigned int shoot_time_out_id=0;
		};
	}
}
#endif
