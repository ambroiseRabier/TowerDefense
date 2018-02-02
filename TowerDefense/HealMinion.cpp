#include "stdafx.h"
#include "HealMinion.hpp"
#include "Timer.hpp"
#include "MinionParams.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense
{
	namespace Game
	{
		HealMinion::HealMinion()
		{
			GameEngine::Debug::warn("HealMinion: defautl constructor should not be used.");
		}

		HealMinion::HealMinion(sf::Vector2u map_pos, sf::Texture* texture, const MinionId minion_id) 
							  : Minion(map_pos, texture, minion_id)
		{
			collider->tag = GameEngine::Collider::Tag::HealMinion;
		}


		HealMinion::~HealMinion()
		{
			if (heal_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(heal_time_out_id);
				heal_time_out_id = 0;
			}
		}

		void HealMinion::on_game_object_overlap(GameObject& game_object)
		{
			if (game_object.get_collider()->tag == GameEngine::Collider::Tag::Minion
			 || game_object.get_collider()->tag == GameEngine::Collider::Tag::HealMinion)
			{
				if (heal_flag)
				{
					Minion* minion = dynamic_cast<Minion*>(&game_object);
					assert(minion);
					minion->get_health().heal(params.heal_others_value);
				}
			}
			// at the end, in case it collide castle and destroy itself.
			Minion::on_game_object_overlap(game_object);
		}

		void HealMinion::start()
		{
			Minion::start();
			start_heal_time_out();
		}

		void HealMinion::update_after_collision()
		{
			// reset heal_flag after collision. (reset will not happen every frame)
			if (heal_flag)
			{
				heal_flag = false;
			}
		}

		void HealMinion::heal_minions()
		{
			heal_time_out_id = 0;
			heal_flag = true;
			start_heal_time_out();
		}

		void HealMinion::start_heal_time_out()
		{
			heal_time_out_id = Utils::Timer::set_time_out(
				Sharp::EventHandler::Bind(&HealMinion::heal_minions, this),
				params.heal_others_delay
			);
		}

	}
}
