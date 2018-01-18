#pragma once
#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "GameObject.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		class Physics
		{
		public:
			static void on_left_click();
			static void on_right_click();
			static std::list<const GameObject*> childrens;
			static sf::Vector2i mouse_position;
			/**
			 * \brief Will trigger mouse and collision events on gameobject.
			 * You need to assign a collider on your gameobject to make it work.
			 * There is no point
			 * \param mono_behaviour 
			 */
			static void addChild(const GameObject& mono_behaviour);
			static void removeChild(const GameObject& mono_behaviour);
			static void update();
		};
	}
}
#endif

