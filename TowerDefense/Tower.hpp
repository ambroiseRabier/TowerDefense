#pragma once
#ifndef TOWER_HPP
#define TOWER_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "ProjectileParams.hpp"
#include "GameObjects/BaseButton.hpp"

namespace TowerDefense
{
	namespace Game
	{
		struct TowerParams;

		/**
		* \brief 
		* Enum representing the tower type, should be unique to class.
		*/
		enum class TowerId
		{
			StoneTower,
			FreezeTower,
			ExplosivTower,
		};
		
		static std::unordered_map<std::string, Game::TowerId> stringToTowerIdEnum = {
			{"StoneTower", TowerId::StoneTower}, {"Stone", TowerId::StoneTower},
			{"FreezeTower", TowerId::FreezeTower}, {"Freeze", TowerId::FreezeTower},
			{"ExplosivTower", TowerId::ExplosivTower}, {"Explosiv", TowerId::ExplosivTower},
		};

		/**
		 * \brief 
		 * Can only be placed on BuildableTile.
		 */
		class Tower : public GameEngine::BaseGameObject
		{
		public:
			Tower();
			Tower(TowerId id, const sf::Vector2u map_pos);
			~Tower();
			void init() override;
			void update() override;
			void on_game_object_overlap(GameObject& game_object) override;
			void on_mouse_overlap() override;
			void update_position();
			TowerId get_tile_id() const;
			void on_game_over();
			const sf::Vector2u map_pos;
			std::unique_ptr<UI::BaseButton> upgrade_btn;
			sf::CircleShape* range_feedback;
			void on_player_money_change();
		private:
			void shoot() const;
			const ProjectileParams& get_current_projectile_params() const;
			const sf::Texture* get_current_projectile_texture() const;
			void reset_shoot_delay();
			void on_projectile_kill();
			float calc_collider_circle_radius() const;
			void upgrade_tower();
			bool is_max_level() const;
			void update_range_feeback();

			/**
			 * \brief Garanted to be valid until tower descontructor.
			 */
			sf::Sprite* sprite;
			TowerId id;
			const TowerParams& params;
			GameObject* target;
			unsigned int level=0;
			unsigned int shoot_time_out_id=0;
		};
	}
}
#endif
