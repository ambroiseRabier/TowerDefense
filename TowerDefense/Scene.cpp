#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
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

		void Scene::addChild(const GameObject& mono_behaviour)
		{
			const bool allready_exit = std::find(childrens.begin(), childrens.end(), &mono_behaviour) != childrens.end();
			if (!allready_exit)
			{
				childrens.push_back(&mono_behaviour);
			}
			else
			{
				Debug::warn("Scene: The element you are trying to push on scene is already on the scene.");
			}
		}

		void Scene::removeChild(const GameObject& mono_behaviour)
		{
			// hope it work the same as in c# :o (don't throw error if not found, find index alone)
			childrens.remove(&mono_behaviour);
		}

		//for (MonoBehaviour* children : childrens)
		void Scene::render(sf::RenderTarget& window)
		{
			childrens.sort(compare_z_index);
			for (const GameObject* children : childrens)
			{
				if (children->get_drawable())
				{
					// combine GameObject "transform" to the GameObject "graphic"
					window.draw(
						*children->get_drawable(),
						children->get_transformable().getTransform()
					);
				}
			}
		}

		bool Scene::compare_z_index (const GameObject* first, const GameObject* second)
		{
			return first->get_zIndex() < second->get_zIndex();
		}
	}
}
