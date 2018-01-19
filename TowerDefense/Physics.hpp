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
			 * \param mono_behaviour 
			 */
			static void addChild(GameObject& gameobject);
			static void removeChild(GameObject& gameobject);
			static void update();
		private:
			static void update_game_object_collision(GameObject& game_object1);
			static void updateMouseCollisions(GameObject& game_object);
			static void updateMouseCollisionFront();
			static bool collision_is_tested(Collider::Tag tag1, Collider::Tag tag2);
			static bool collision_is_tested(std::pair<Collider::Tag, Collider::Tag> tag_pair);
			static bool collide_mouse(const GameObject& game_object);
			static bool left_clicked;
			static bool right_clicked;
		};
	}
}
#endif

