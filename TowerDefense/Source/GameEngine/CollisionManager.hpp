#pragma once
#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP
#include "GameObject.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		/**
		 * \brief 
		 *  The name is a bit misleading, if you compare to unity, all the collision box are isTrigger=true.
		 *  Handle collisions between gameobjects, and between mouse and gameobjects, using their collider.
		 *  A gameobject callback is called when an event happen.
		 *  -------
		 *  YOU CANNOT destroy an object inside the collision or this will result in an exception.
		 *  If CollisionManager and DisplayManager were having the autority on memory of the objects I would not have this problem.
		 *  (That's why unity use Global function Destroy ?)
		 */
		class CollisionManager
		{
		public:
			static void init(std::vector<std::pair<Collider::Tag, Collider::Tag>> configTestedCollisions);
			static void on_left_click();
			static void on_right_click();
			// is not const GameObject* because I need to call some function inside.
			static std::list<GameObject*> childrens;
			static sf::Vector2i mouse_position;
			static std::vector<std::pair<Collider::Tag, Collider::Tag>> testedCollisions;
			static std::vector<GameObject*> mouseCollisionBuffer;

			/**
			 * \brief Will trigger mouse and collision events on gameobject.
			 * You need to assign a collider on your gameobject to make it work.
			 * There is no point
			 * \param gameobject
			 */
			static void addChild(GameObject& gameobject);
			static void removeChild(GameObject& gameobject);
			static void update();
		private:
			static void update_game_object_collision(GameObject& game_object1);
			static void updateMouseCollisions(GameObject& game_object);
			static bool validMouseCollider(const GameObject& game_object);
			static void updateMouseCollisionFront();
			static bool has_valid_tag_pair(Collider::Tag tag1, Collider::Tag tag2);
			static bool has_valid_tag_pair(std::pair<Collider::Tag, Collider::Tag> tag_pair);
			static bool collide_mouse(const GameObject& game_object);
			static bool left_clicked;
			static bool right_clicked;
		};
	}
}
#endif

