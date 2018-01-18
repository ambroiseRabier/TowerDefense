#include "Scene.hpp"
#include "stdafx.h"
#include "Debug.hpp"

using namespace std;
namespace TowerDefense
{
	namespace GameEngine
	{
		std::list<const GameObject*> Scene::childrens;

		void Scene::init()
		{

		}

		void Scene::addChild(const GameObject& gameobject)
		{
			const bool allready_exit = std::find(childrens.begin(), childrens.end(), &gameobject) != childrens.end();
			if (!allready_exit)
			{
				Debug::assert_m((&gameobject)->get_drawable(), "Scene: A gameobject you add to the scene should have a drawable setted.");
				childrens.push_back(&gameobject);
			}
			else
			{
				Debug::warn("Scene: The element you are trying to push on scene is already on the scene.");
			}
		}

		void Scene::removeChild(const GameObject& gameobject)
		{
			childrens.remove(&gameobject);
		}

		void Scene::render(sf::RenderTarget& window)
		{
			childrens.sort(GameObject::compare_z_index);
			for (const GameObject* children : childrens)
			{
				// well, you could remove the drawable without error, but that is not encouraged.
				if (children->isVisible && children->get_drawable())
				{
					// combine GameObject "transform" to the GameObject "graphic"
					window.draw(
						*children->get_drawable(),
						children->get_transformable().getTransform()
					);
				}
			}
		}
	}
}
