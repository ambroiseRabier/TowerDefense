#include "stdafx.h"
#include "Physics.hpp"
#include "GameObject.hpp"
#include "Debug.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		std::list<const GameObject*> Physics::childrens;
		sf::Vector2i Physics::mouse_position;

		void Physics::addChild(const GameObject& gameobject)
		{
			const bool allready_exit = std::find(childrens.begin(), childrens.end(), &gameobject) != childrens.end();
			if (!allready_exit)
			{
				Debug::assert_m((&gameobject)->get_collider().get(), "Physics: A gameobject you add to the scene should have a collider setted.");
				childrens.push_back(&gameobject);
			}
			else
			{
				Debug::warn("Physics: The element you are trying to push on scene is already on the scene.");
			}
		}

		void Physics::removeChild(const GameObject& mono_behaviour)
		{
			childrens.remove(&mono_behaviour);
		}

		void Physics::update()
		{
			// yes this look like a duplicate of scene, but I think it's better to have a clear separation between both.
			childrens.sort(GameObject::compare_z_index);
			for (const GameObject* children : childrens)
			{
				// well, you could remove the collider without error, but that is not encouraged.
				if (children->get_collider())
				{
					if (children->get_collider()->gameobject_enabled)
					{
						//todo
					}
					if (children->get_collider()->mouse_enabled)
					{
						
					}
				}
			}
		}

		void Physics::on_left_click()
		{
		}

		void Physics::on_right_click()
		{
		}
	}
}
