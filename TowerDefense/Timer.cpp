#include "stdafx.h"
#include "Timer.hpp"
#include "GlobalShared.hpp"
#include "MapManager.hpp"
#include "Managers/GameManager.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense
{
	namespace Utils
	{
		std::list<DestroyWithId> Timer::all_destroy;
		std::list<TimeOutWithId> Timer::all_time_out;
		sf::Clock Timer::clock;
		std::list<unsigned int> Timer::id_used_list;

		void Timer::init()
		{
			// if we need those outside of the map,
			// I recommend using a bool in struct to indicate if it is to be destroyed with the map.
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(on_quit_game);
			Managers::MapManager::on_destroy_level += Sharp::EventHandler::Bind(on_map_destroyed);
		}

		// will be called two times if quit game happen when map is here. It's ok.
		void Timer::on_quit_game()
		{
			if (!all_destroy.empty())
			{
				for (auto element : all_destroy)
				{
					delete element.to_destroy;
				}
				all_destroy.clear();
			}
			if (!all_time_out.empty())
			{
				for (auto time_out : all_time_out)
				{
					delete time_out.to_call;
					time_out.to_call = nullptr;
				}
				all_time_out.clear();
			}
		}

		// for now it's a copy of on_quite_game, might change later if timer are needed in UI.
		void Timer::on_map_destroyed()
		{
			on_quit_game();
		}

		const unsigned int Timer::generate_id()
		{
			unsigned int id;
			const unsigned int max_unsigned_int_size = std::numeric_limits<unsigned int>::max();
			for (int i = 1; i < max_unsigned_int_size; ++i)
			{
				const bool found = std::find(id_used_list.begin(), id_used_list.end(), i) != id_used_list.end();
				if (!found)
				{
					id = i;
					break;
				}
			}
			id_used_list.push_back(id);
			return id;
		}

		void Timer::free_id(const unsigned int& id)
		{
			id_used_list.remove(id);
		}

		const unsigned int Timer::destroy(GameEngine::GameObject* pointer, float delay, bool fixed_time)
		{
			const unsigned int id = generate_id();
			all_destroy.push_back(DestroyWithId(
				pointer, 
				get_current_time(fixed_time) + delay,
				id, 
				fixed_time
			));
			return id;
		}

		const unsigned int Timer::set_time_out(Sharp::EventHandlerImpl<void>* callback, float delay, bool fixed_time)
		{
			const unsigned int id = generate_id();
			all_time_out.push_back(TimeOutWithId(
				callback, 
				get_current_time(fixed_time) + delay,
				id, 
				fixed_time
			));
			return id;
		}

		const float Timer::get_current_time(bool fixed_time)
		{
			return fixed_time ? clock.getElapsedTime().asSeconds() : static_cast<float>(Managers::GameManager::get_clock());
		}
		
		void Timer::cancel_destroy(const unsigned int& id)
		{
			GameEngine::Debug::assert_m(id != 0, "0 means no id, it is used as null value");
			for (auto destroy : all_destroy)
			{
				if (destroy.id == id)
				{
					all_destroy.erase(
						std::remove(all_destroy.begin(), all_destroy.end(), destroy), all_destroy.end()
					);
					free_id(id);
					return;
				}
			}
		}

		void Timer::cancel_set_time_out(const unsigned int& id)
		{
			GameEngine::Debug::assert_m(id != 0, "0 means no id, it is used as null value");
			for (auto time_out : all_time_out)
			{
				if (time_out.id == id)
				{
					delete time_out.to_call;
					time_out.to_call = nullptr;
					all_time_out.erase(
						std::remove(all_time_out.begin(), all_time_out.end(), time_out), all_time_out.end()
					);
					free_id(id);
					return;
				}
			}
		}

		void Timer::update()
		{
			if (!all_destroy.empty())
			{
				update_all_destroy();
			}

			if (!all_time_out.empty())
			{
				update_all_time_out();
			}
		}

		void Timer::update_all_destroy()
		{
			for (auto it = all_destroy.begin(); it != all_destroy.end();)
			{
				// your time has come to and end.
				const bool out_of_date = it->fixed_time ?
					it->end_time <= clock.getElapsedTime().asSeconds()
				  : it->end_time <= Managers::GameManager::get_clock();

				if (out_of_date)
				{
					delete it->to_destroy;
					free_id(it->id);
					it = all_destroy.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		void Timer::update_all_time_out()
		{
			for (auto it = all_time_out.begin(); it != all_time_out.end();)
			{
				// your time has come to and end.
				const bool out_of_date = it->fixed_time ?
					it->end_time <= clock.getElapsedTime().asSeconds()
				  : it->end_time <= Managers::GameManager::get_clock();

				if (out_of_date)
				{
					// problem if I had an timeout inside the callback.
					
					call_that_for_me(it->to_call);
					if (it->to_call)
					{
						delete it->to_call;
						it->to_call = nullptr;
					}
					free_id(it->id);
					it = all_time_out.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
				
		void Timer::call_that_for_me(Sharp::EventHandlerImpl<void>* pHandlerToAdd)
		{
			if (pHandlerToAdd)
			{
				pHandlerToAdd->OnEvent();
			}
		}
	}
}
