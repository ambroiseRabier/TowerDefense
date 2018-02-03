#include "stdafx.h"
#include "Scene.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
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
