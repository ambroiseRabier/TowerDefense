#include "stdafx.h"
#include "Scene.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		// WIP CLASS: supposed to manage memory more clearly, 
		// maybe manage update call
		// and also replace Destroyer class.
		// to have a centralised memory management for gameobjects.
		std::list<std::shared_ptr<GameObject>> Scene::game_object_list;

		void Scene::destroy(GameObject& game_object)
		{
			for (auto&& shared_ptr : Scene::game_object_list)
			{
				if (*shared_ptr.get() == game_object)
				{
					shared_ptr.reset();
					game_object_list.remove(shared_ptr);
					break;
				}
			}
		}
	}
}
