#include "stdafx.h"
#include "Physics.hpp"
#include "GameObject.hpp"
#include "Debug.hpp"
#include "CollisionTest.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		std::list<GameObject*> Physics::childrens;
		sf::Vector2i Physics::mouse_position;
		std::vector<std::pair<Collider::Tag, Collider::Tag>> Physics::testedCollisions;
		std::vector<GameObject*> Physics::mouseCollisionBuffer;
		bool Physics::left_clicked;
		bool Physics::right_clicked;


		void Physics::init(std::vector<std::pair<Collider::Tag, Collider::Tag>> configTestedCollisions)
		{
			testedCollisions = configTestedCollisions;
		}

		void Physics::addChild(GameObject& game_object)
		{
			const bool allready_exit = std::find(childrens.begin(), childrens.end(), &game_object) != childrens.end();
			if (!allready_exit)
			{
				Debug::assert_m(
					(&game_object)->get_collider().get(),
					"Physics: A gameobject you add to the physic should have a collider setted."
				);
				Debug::assert_m(
					(&game_object)->get_collider()->tag != Collider::Tag::None,
					"Physics: The collider you are adding has None tag setted that is invalid. (if you insist to have None then don't put any collider)"
				);
				Debug::assert_m(
					(&game_object)->get_collider()->get_type() != Collider::Type::None,
					"Physics: The collider you are adding has None type setted that is invalid. (if you insist to have None then don't put any collider)"
				);
				childrens.push_back(&game_object);
			}
			else
			{
				Debug::warn("Physics: The element you are trying to push on scene is already on the scene.");
			}
		}

		void Physics::removeChild(GameObject& game_object)
		{
			childrens.remove(&game_object);
		}

		/**
		 * \brief Test collisions and send event to GameObjects
		 * Calling the collider would a bit more sense regarding oriented object design
		 * But it is more KISS to call GameObject instead.
		 */
		void Physics::update()
		{
			// yes this look like a duplicate of scene, but I think it's better to have a clear separation between both.
			childrens.sort(GameObject::compare_z_index_p);
			for (GameObject* children : childrens)
			{
				// well, you could remove the collider without error, but that is not encouraged.
				// better use gameobject_enabled && mouse_enabled
				if (children->get_collider())
				{
					if (children->get_collider()->gameobject_enabled)
					{
						update_game_object_collision(*children);
					}
					if (children->get_collider()->mouse_enabled)
					{
						updateMouseCollisions(*children);
					}
				}
			}
			updateMouseCollisionFront();
			left_clicked = false;
			right_clicked = false;
			mouseCollisionBuffer.clear();
		}

		void Physics::updateMouseCollisions(GameObject& game_object)
		{
			if (collide_mouse(game_object))
			{
				game_object.on_mouse_overlap();
				if (left_clicked)
				{
					game_object.on_mouse_click(false);
				}
				if (right_clicked)
				{
					game_object.on_mouse_click(true);
				}
				mouseCollisionBuffer.push_back(&game_object); // huum bon pointeur?
			}
		}

		/**
		 * \brief Depend on updateMouseCollisions
		 */
		void Physics::updateMouseCollisionFront()
		{
			if (!mouseCollisionBuffer.empty())
			{
				GameObject* game_object_hightest_z = *std::max_element(
					mouseCollisionBuffer.begin(),
					mouseCollisionBuffer.end(),
					GameObject::compare_z_index_p
				);
				if (game_object_hightest_z->get_collider()->mouse_enabled)
				{
					game_object_hightest_z->on_mouse_overlap_front();
					if (left_clicked)
					{
						game_object_hightest_z->on_mouse_click_front(false);
					}
					if (right_clicked)
					{
						game_object_hightest_z->on_mouse_click_front(true);
					}
				}
			}
		}

		void Physics::update_game_object_collision(GameObject& game_object)
		{
			for (GameObject* children2 : childrens)
			{
				const bool should_test_collision = collision_is_tested(
					game_object.get_collider()->tag,
					children2->get_collider()->tag
				);
				if (should_test_collision)
				{
					// this make lot of useless calls. Could be optimize
					// and if someone destroy the object right when on_game_object_overlap then bug. no ?
					if (CollisionTest::collide(*game_object.get_collider(), *children2->get_collider()))
					{
						game_object.on_game_object_overlap(*children2);
					}
				}
			}
		}

		bool Physics::collision_is_tested(Collider::Tag tag1, Collider::Tag tag2) 
		{
			bool result = false;
			for (std::pair<Collider::Tag, Collider::Tag> pair : testedCollisions)
			{
				// test a matching pair, order is of pair is ignored.
				if ((pair.first == tag1 
					&& pair.second == tag2)
					|| (pair.first == tag2 
					&& pair.second == tag1))
				{
					result = true;
				}
			}
			return result;
		}
		
		bool Physics::collide_mouse(const GameObject& game_object)
		{
			if (game_object.get_collider()->get_type() == Collider::Type::Rect)
			{
				return CollisionTest::rect_dot(
					game_object.get_collider()->get_rect(),
					game_object.to_local(
						static_cast<sf::Vector2f>(mouse_position)
					)
				);
			}
			Debug::warn("Physics WIP: collider type not supported.");
			return false;
		}
		
		bool Physics::collision_is_tested(std::pair<Collider::Tag, Collider::Tag> pair)
		{
			return collision_is_tested(pair.first, pair.second);
		}

		void Physics::on_left_click()
		{
			left_clicked = true;
		}

		void Physics::on_right_click()
		{
			right_clicked = true;
		}
	}
}