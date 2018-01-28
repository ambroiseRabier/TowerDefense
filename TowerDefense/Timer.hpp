#pragma once
#ifndef TIMER_HPP
#define TIMER_HPP
#include "GameEngine/GameObject.hpp"
#include "Utils/Event.h"

namespace TowerDefense
{
	namespace Utils
	{
		struct DestroyWithId
		{
			friend bool operator==(const DestroyWithId& lhs, const DestroyWithId& rhs)
			{
				return lhs.id == rhs.id;
			}

			friend bool operator!=(const DestroyWithId& lhs, const DestroyWithId& rhs)
			{
				return !(lhs == rhs);
			}

			DestroyWithId(GameEngine::GameObject* to_destroy, float delay, unsigned int id)
				: to_destroy(to_destroy),
				  delay(delay),
				  id(id)
			{
			}

			GameEngine::GameObject* to_destroy;
			float delay;
			unsigned int id;
		};

		struct TimeOutWithId
		{
			friend bool operator==(const TimeOutWithId& lhs, const TimeOutWithId& rhs)
			{
				return lhs.id == rhs.id;
			}

			friend bool operator!=(const TimeOutWithId& lhs, const TimeOutWithId& rhs)
			{
				return !(lhs == rhs);
			}

			TimeOutWithId(Sharp::EventHandlerImpl<void>* to_call, float delay, unsigned int id)
				: to_call(to_call),
				  delay(delay),
				  id(id)
			{
			}

			Sharp::EventHandlerImpl<void>* to_call;
			float delay;
			unsigned int id;
		};

		// tested with that.
		/*
		UI::BaseButton* base_button = new UI::BaseButton();
		base_button->get_transformable().setPosition(150,150);
		base_button->auto_start();
		auto ss = Utils::Timer::destroy(base_button, 5.f);
		UI::BaseButton* base_button2 = new UI::BaseButton();
		base_button2->get_transformable().setPosition(20,200);
		base_button2->auto_start();
		auto ss2 = Utils::Timer::destroy(base_button2, 5.f);
		Utils::Timer::cancel_destroy(ss);
		Utils::Timer::cancel_destroy(ss2);*/

		/* tested with that
		 	UI::BaseButton* base_button = new UI::BaseButton();
	base_button->get_transformable().setPosition(150,150);
	//base_button->auto_start();
	auto cc = Sharp::EventHandler::Bind<UI::BaseButton>(&UI::BaseButton::auto_start, base_button);
	auto ss = Utils::Timer::set_time_out(cc, 3.f);
	Utils::Timer::cancel_set_time_out(ss);*/

		/**
		 * \brief 
		 * All timer precision depend on framerate, so they are not exact at all ! (can be one frame imprecise)
		 */
		class Timer
		{
		public:
			static void init();

			/**
			 * \brief Designed to work with elements dependant of the map. 
			 * (all destroy will be resetted when map is destroyed)
			 * YOU ENGAGE YOURSELF TO NOT DESTROY THE OBJECT WHEN USING THIS FUNCTION.
			 * If you need to destroy the object be sure to remove it from Timer.
			 * todo: make unique ptr ?
			 * \param pointer 
			 * \param delay 
			 */
			static const unsigned destroy(GameEngine::GameObject* pointer, float delay);

			/**
			 * \brief Designed to work with elements dependant of the map. 
			 * (all callbakc are stopped if map is destroyed)
			 * \param callback 
			 * \param delay 
			 * \return 
			 */
			static const unsigned int set_time_out(Sharp::EventHandlerImpl<void>* callback, float delay);

			/**
			 * \brief 
			 * Cancel the destroy using the id provided by destroy function.
			 * If id is not found it does nothing.
			 * \param id 
			 */
			static void cancel_destroy(const unsigned int& id);

			/**
			 * \brief 
			 * Cancel the callback using the id provided by set_time_out function.
			 * If id is not found it does nothing.
			 * \param id 
			 */
			static void cancel_set_time_out(const unsigned int& id);
			static void update();
		private:
			static std::vector<DestroyWithId> all_destroy;
			static std::vector<TimeOutWithId> all_time_out;
			static sf::Clock clock;
			static std::list<unsigned int> id_used_list;
			static void on_quit_game();
			static void on_map_destroyed();

			/**
			 * \brief Generate an unique id based on actually used id. (collision impossible)
			 * \return 
			 */
			static const unsigned generate_id();

			/**
			 * \brief Free Id to be re-used.
			 * \param id 
			 */
			static void free_id(const unsigned int& id);
			static void update_all_destroy();
			static void update_all_time_out();
			static void call_that_for_me(Sharp::EventHandlerImpl<void>* pHandlerToAdd);
		};

	}
}
#endif
