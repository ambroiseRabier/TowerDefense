#include "stdafx.h"
#include "Physics.hpp"
#include "GameObject.hpp"
#include "Debug.hpp"

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

		bool Physics::collide_mouse(const GameObject& game_object)
		{
			if (game_object.get_collider()->get_type() == Collider::Type::Rect)
			{
				// mouse_position.toLocal(game_object)
				return game_object.get_collider()->get_rect().contains(
					game_object.to_local(static_cast<sf::Vector2f>(mouse_position))
				);
			}
			Debug::warn("Physics WIP: collider type not supported.");
			return false;
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
				if (children->get_collider())
				{
					if (children->get_collider()->gameobject_enabled)
					{
						for (const GameObject* children2 : childrens)
						{
							//if ()
						}
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
			if (game_object.get_collider()->mouse_enabled)
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
		}

		void Physics::updateMouseCollisionFront()
		{
			if (!mouseCollisionBuffer.empty())
			{
				GameObject* game_object_hightest_z = *std::max_element(
					mouseCollisionBuffer.begin(),
					mouseCollisionBuffer.end(),
					GameObject::compare_z_index_p
				);
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
