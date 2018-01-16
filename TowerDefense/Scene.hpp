#pragma once
#include "MonoBehaviour.hpp"
#include <list>

namespace TowerDefense
{
	namespace GameEngine
	{
		class Scene
		{
		public:
			//Scene();
			//~Scene();
			static void init();
			static void update();
			/**
			 * \brief Add and draw the MonoBehaviour from scene. 
			 * (I use reference instead of pointer because the pointer you use to create the MonoBehaviour might become null.
			 * And the MonoBehaviour should be able to remove from Scene::childrens at any time.)
			 * \param mono_behaviour 
			 */
			static void add(const MonoBehaviour& mono_behaviour);
			/**
			 * \brief Remove the MonoBehaviour from scene. (won't be draw anymore)
			 * \param mono_behaviour 
			 */
			static void remove(const MonoBehaviour& mono_behaviour);
						
			/**
			 * \brief Render with zIndex.
			 * \param window
			 * \param target 
			 * \param states 
			 */
			static void render(sf::RenderTarget& window);
			static bool compare_z_index(const MonoBehaviour* first, const MonoBehaviour* second);

			// debug shot hitbox bool ?
		private:
			static std::list<const MonoBehaviour*> childrens;
		};
	}
}
