#include "stdafx.h"
#include "MapWaveManager.hpp"
#include "Minion.hpp"
#include "GlobalShared.hpp"
#include "MapManager.hpp"
#include "Timer.hpp"
#include "GameEngine/Debug.hpp"
#include "Hud.hpp"
#include "Config.hpp"

using namespace TowerDefense::Game;
namespace TowerDefense
{
	namespace Managers
	{
		std::list<BaseGameObject*> MapWaveManager::instanciated_elements;
		const MapParams* MapWaveManager::map_params;
		unsigned int MapWaveManager::wave_index;
		unsigned int MapWaveManager::minion_wave_index;
		unsigned int MapWaveManager::minion_time_out_id;
		unsigned int MapWaveManager::minion_wave_time_out_id;

		void MapWaveManager::init()
		{
			// no need to unlisten the event, since MapManager.on_destroy_level gonna be destroyed anyway.
			MapManager::on_destroy_level += Sharp::EventHandler::Bind(&MapWaveManager::destroy_current_level);
		}

		void MapWaveManager::load_minions(const MapParams* new_map_params)
		{
			assert(new_map_params != nullptr);
			map_params = new_map_params;
			// you can do some poooling here and load minions.
		}

		void MapWaveManager::start()
		{
			wave_index = 0;
			minion_wave_index = 0;
			if(!is_end_of_level()) {
				next_wave();
			} 
			else
			{
				Debug::warn("Your level has no waves (no minions).");
			}
		}

		void MapWaveManager::next_wave()
		{
			minion_time_out_id = 0;
			minion_wave_index = 0;
			UI::Hud::set_wave_text(Constants::Config::wave_number_text + " " + std::to_string(wave_index));
			
			if (!is_end_of_level())
			{
				next_minon_wave();
			} else
			{
				UI::Hud::set_wave_text(Constants::Config::final_wave_text);
			}
		}

		void MapWaveManager::next_minon_wave()
		{
			minion_wave_time_out_id = 0;
			assert(!is_end_of_level());

			if (is_end_of_wave())
			{
				if (next_minion_wave_valid())
				{
					minion_time_out_id = Utils::Timer::set_time_out(
						Sharp::EventHandler::Bind(&MapWaveManager::next_wave),
						get_delay_before_next_wave()
					);
					wave_index++;
				} 
				else
				{
					Debug::warn("MapWaveManager: empty wave detected, skipping");
					wave_index++;
					next_wave();
				}
			}
			else
			{
				if (next_minion_wave_valid())
				{
					spawn(
						map_params->wave_params_vector.at(wave_index)
						.minion_params_vector.at(minion_wave_index).minion_id
					);
					// note: if delay is 0 it is going to be launched next frame.
					// so minion_wave_index will be incremented before
					// but not before get_delay_before_next_minion_wave() is called.
					minion_wave_time_out_id = Utils::Timer::set_time_out(
						Sharp::EventHandler::Bind(&MapWaveManager::next_minon_wave),
						get_delay_before_next_minion_wave()
					);
					minion_wave_index++;
				} 
				else
				{
					Debug::warn("MapWaveManager: empty minion wave detected, skipping");
					minion_wave_index++;
					next_minon_wave();
				}
			}
		}

		void MapWaveManager::spawn(const Game::MinionId& minion_id)
		{
			Minion* minion;
			switch (minion_id)
			{
			case Peon: 
				minion = Minion::create_peon(MapManager::get_spawn().map_pos);
				break;
			case Tank:
				minion = Minion::create_peon(MapManager::get_spawn().map_pos);
				break;
			case Heal: 
				minion = Minion::create_peon(MapManager::get_spawn().map_pos);
				break;
			default:
				Debug::warn(
					"MapWaveManager: You forgot to update MapWaveManbager after adding a new minion. As result the minion is not spawned."
				);
				return;
			}
			minion->get_transformable().setPosition(
				MapManager::get_spawn().get_transformable().getPosition()
			);
			minion->auto_start();
			instanciated_elements.push_back(minion);
		}

		const float MapWaveManager::get_delay_before_next_wave()
		{
			return abs(map_params->wave_params_vector.at(wave_index).delay_before_next);
		}

		const float MapWaveManager::get_delay_before_next_minion_wave()
		{
			return abs(map_params->wave_params_vector.at(wave_index)
				.minion_params_vector.at(minion_wave_index).delay_before_next);
		}

		bool MapWaveManager::next_wave_valid()
		{
			return !map_params->wave_params_vector.empty();
		}

		bool MapWaveManager::next_minion_wave_valid()
		{
			return !map_params->wave_params_vector.at(wave_index)
				.minion_params_vector.empty();
		}

		bool MapWaveManager::is_end_of_wave()
		{
			return minion_wave_index == map_params->wave_params_vector.at(wave_index)
				.minion_params_vector.size();
		}

		bool MapWaveManager::is_end_of_level()
		{
			 return wave_index == map_params->wave_params_vector.size();
		}

		void MapWaveManager::destroy_me(BaseGameObject& to_delete)
		{
			// this obviously do not work, because the pointer is different.
			// we have to search by value.
			//instanciated_elements.remove(&base_game_object);
			for (auto base_game_object : instanciated_elements)
			{
				if (to_delete == *base_game_object)
				{
					instanciated_elements.remove(base_game_object);
					delete base_game_object;
					base_game_object = nullptr;
					break;
				}
			}
		}

		void MapWaveManager::remove_me(const BaseGameObject& to_remove)
		{
			for (auto base_game_object : instanciated_elements)
			{
				if (to_remove == *base_game_object)
				{
					instanciated_elements.remove(base_game_object);
					break;
				}
			}
		}

		void MapWaveManager::destroy_current_level()
		{
			if (minion_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(minion_time_out_id);
				minion_time_out_id = 0;
			}
			if (minion_wave_time_out_id != 0)
			{
				Utils::Timer::cancel_set_time_out(minion_wave_time_out_id);
				minion_wave_time_out_id = 0;
			}

			if (!instanciated_elements.empty())
			{
				for (std::list<GameEngine::BaseGameObject*>::value_type base_game_object : instanciated_elements)
				{
					delete base_game_object;
					base_game_object = nullptr;
				}
				instanciated_elements.clear();
			}
			map_params = nullptr;
			wave_index = 0;
			minion_wave_index = 0;
		}
	}
}
