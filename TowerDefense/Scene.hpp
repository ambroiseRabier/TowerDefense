#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP
#include "GameObject.hpp"
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
			static void addChild(const GameObject& mono_behaviour);
			/**
			 * \brief Remove the MonoBehaviour from scene. (won't be draw anymore)
			 * \param mono_behaviour 
			 */
			static void removeChild(const GameObject& mono_behaviour);
						
			/**
			 * \brief Render with zIndex.
			 * \param window
			 * \param target 
			 * \param states 
			 */
			static void render(sf::RenderTarget& window);

			// debug shot hitbox bool ?
		private:
			static std::list<const GameObject*> childrens;
		};
	}
}
#endif
