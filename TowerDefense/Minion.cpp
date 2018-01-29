#include "stdafx.h"
#include "Minion.hpp"
#include "../../CastUtils.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"
#include "Managers/GameManager.hpp"
#include "Mathf.hpp"
#include "MapManager.hpp"
#include "Assets.hpp"
#include "GameEngine/Debug.hpp"
#include "MinionParams.hpp"
#include "GameDesign.hpp"
#include "Timer.hpp"
#include "AssetsConfig.hpp"
#include "MapWaveManager.hpp"

using namespace TowerDefense::Utils;
namespace TowerDefense
{
	namespace Game
	{
		Minion* Minion::create_peon(const sf::Vector2u& map_pos)
		{
			return new Minion(map_pos, GlobalShared::minion_red_texture, MinionId::Peon);
		}
		
		Minion::Minion() : params(MinionParams())  // NOLINT
		{
			Debug::warn("Minon: default contructor not supposed to be called.");
		}

		Minion::Minion(sf::Vector2u map_pos, sf::Texture* texture, const MinionId minion_id) 
					  : map_pos(map_pos), params(Constants::GameDesign::minions.at(minion_id)), previous_map_pos(map_pos)
		{
			std::unique_ptr<sf::Sprite> my_sprite = std::make_unique<sf::Sprite>(*GlobalShared::minion_red_texture);

			sprite = my_sprite.get();
			set_drawable(
				std::move(static_cast_ptr<sf::Drawable>(
					my_sprite
				))
			);
			collider = std::make_shared<Collider>(
				sprite->getLocalBounds(),
				Collider::Tag::Minion
			);
			z_index = Constants::ZIndex::minions_start;
			health = std::make_unique<Health>(params.health);
			update_health_pos();
			health->auto_start();
		}

		Minion::~Minion()
		{
			health.reset(nullptr);
		}

		Health& Minion::get_health() const
		{
			return *health;
		}

		void Minion::init()
		{
			BaseGameObject::init();
			assert(health);
			health->on_death += Sharp::EventHandler::Bind(&Minion::on_death, this);
			death_time_out_id = 0;
		}

		void Minion::on_destroy_map()
		{
			// this is probably not needed.
			health->on_death -= Sharp::EventHandler::Bind(&Minion::on_death, this);
			// cancel timer if map is destroyed while the timer is active.
			// if there is no timer does nothing.
			// don't put that in on_death or descontructor, 
			// or you will remove a pointer reference in Timer and it will crash.
			if (death_time_out_id != 0)
			{
				Timer::cancel_set_time_out(death_time_out_id);
			}
			Managers::MapWaveManager::temp_minion = nullptr;
			delete this;
		}

		void Minion::on_death()
		{
			// use a juicy new texture as feedback
			sprite->setTexture(*GlobalShared::minion_death_texture);
			// make the collider inactive.
			collider->gameobject_enabled = false;
			collider->mouse_enabled = false;
			// set a timer before destroying this instance.
			death_time_out_id = Timer::set_time_out(
				Sharp::EventHandler::Bind(&Minion::destroy_self, this),
				Constants::AssetsConfig::minion_death_delay
			);
		}

		void Minion::destroy_self()
		{
			// don't let the MapManager destroy yourself a second time. (don't put thyat in on_death since map destroy has priority.
			Managers::MapWaveManager::temp_minion = nullptr;
			Debug::log("I probably get problems from here !");
			delete this;
		}

		void Minion::start()
		{
			next_map_pos = find_next_map_pos(map_pos);
			BaseGameObject::start();
		}

		void Minion::update() // todo: split in parts.
		{
			sf::Vector2f target_pos = Tile::map_pos_to_global_pos(next_map_pos);
			const float speed = params.speed * Constants::Assets::tile_size * Managers::GameManager::get_delta_time();
			float dist = magnitude(target_pos - transformable->getPosition());
			bool overpass_target = dist < speed;
			// if gonna overpass target_pos,save current map_pos, then calculate new target, if new target == previous target, do nothing.
			// change direction
			if (overpass_target)
			{
				previous_map_pos = map_pos;
				map_pos = next_map_pos;
				next_map_pos = find_next_map_pos(map_pos);
				if (map_pos != next_map_pos)
				{
					target_pos = Tile::map_pos_to_global_pos(next_map_pos);
					dist = magnitude(target_pos - transformable->getPosition());
					overpass_target = dist < speed;
				}
				// else stay on overpass_target == true
			}
			// moving normally.
			if (!overpass_target)
			{
				const float rotation_to_target = calc_rotation(target_pos);
				//assert(get_drawable_transformable());
				// do not move hitbox, only graphic.
				// todo: need to move graphic, but form it's center, not from it's top left :/
				/*get_drawable_transformable()->setRotation(
					rotation_to_target
				);*/
				transformable->setPosition(
					calc_pos(target_pos, speed)
				);
				// degree and radian are so error prone :/ and hard to debug !
				/*transformable->setPosition(
					calc_position(rotation_to_target, speed)
				);*/
			} 
			// here we are stuck in a dead end.
			else
			{ // will run every frame for nothing ? (do else if with check if alreayd on pos) ?
				/*transformable->setRotation(
					0
				);*/
				transformable->setPosition(
					target_pos
				);
			}
			update_health_pos();
		}

		sf::Vector2f Minion::calc_pos(const sf::Vector2f& target_pos, const float& speed) const
		{
			const sf::Vector2f dir(normalize(target_pos - transformable->getPosition()));
			return transformable->getPosition() + dir * speed;
		}

		sf::Vector2f Minion::calc_position(const float& rotation, const float& speed) const
		{
			sf::Vector2f new_pos(transformable->getPosition());
			new_pos.x += static_cast<float>(std::cos(rotation / 180.f * M_PI) * speed);
			new_pos.y += static_cast<float>(std::sin(rotation / 180.f * M_PI) * speed);
			return new_pos;
		}

		float Minion::calc_rotation(const sf::Vector2f& rotateTo) const
		{
			// return double, but float is enough precision.
			return static_cast<float>(std::atan2f(
				rotateTo.y - transformable->getPosition().y, 
				rotateTo.x - transformable->getPosition().x
			) / M_PI * 180.f);
		}

		sf::Vector2u Minion::find_next_map_pos(const sf::Vector2u& current_map_pos) const
		{
			const sf::Vector2u next_front(current_map_pos.x + 1, current_map_pos.y);
			const sf::Vector2u next_top(current_map_pos.x, current_map_pos.y - 1);
			const sf::Vector2u next_bottom(current_map_pos.x, current_map_pos.y + 1);
			const sf::Vector2u next_back(current_map_pos.x -1, current_map_pos.y); // usefull for making the minion infinite loop for debug tower.
			const bool front_ok =  validate_pos(next_front);
			const bool top_ok = validate_pos(next_top);
			const bool bottom_ok = validate_pos(next_bottom);
			const bool back_ok = validate_pos(next_back);
			if (front_ok) return next_front;
			if (top_ok && bottom_ok) return rand_bool() ? next_top : next_bottom;
			if (top_ok) return next_top;
			if (bottom_ok) return next_bottom;
			if (back_ok) return next_back;
			return current_map_pos;
			// could slightly optimize function, but let's keep it visible.
		}

		bool Minion::validate_pos(const sf::Vector2u& new_pos) const
		{
			return previous_map_pos != new_pos
				&& Managers::MapManager::map_pos_exist(new_pos) 
				&& Managers::MapManager::map_pos_walkable(new_pos);
		}

		void Minion::update_health_pos()
		{
			const sf::Vector2f offset(0, -25.f); // from center of tile.
			health->get_transformable().setPosition(
				transformable->getPosition() + Constants::Assets::tile_size_half_vec + offset
			);
		}
	}
}
