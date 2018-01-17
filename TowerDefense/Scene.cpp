#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "stdafx.h"

using namespace std;
namespace TowerDefense
{
	namespace GameEngine
	{
		std::list<const MonoBehaviour*> Scene::childrens;

		void Scene::init()
		{

		}

		void Scene::addChild(const MonoBehaviour& mono_behaviour)
		{
			childrens.push_back(&mono_behaviour);
		}

		void Scene::removeChild(const MonoBehaviour& mono_behaviour)
		{
			// hope it work the same as in c# :o (don't throw error if not found, find index alone)
			childrens.remove(&mono_behaviour);
		}

		//for (MonoBehaviour* children : childrens)
		void Scene::render(sf::RenderTarget& window)
		{
			childrens.sort(compare_z_index);
			for (const MonoBehaviour* children : childrens)
			{
				if (children->get_drawable())
				{
					window.draw(*children->get_drawable()); // todo: add transform ?
				}
			}
		}

		bool Scene::compare_z_index (const MonoBehaviour* first, const MonoBehaviour* second)
		{
			return first->get_zIndex() < second->get_zIndex();
		}
	}
}
