#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP
#include "GameObject.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		/**
		 * \brief 
		 * Display all gameobjects that you add on the DisplayManager with z-sorting.
		 */
		class DisplayManager
		{
		public:
			//DisplayManager();
			//~DisplayManager();
			static void init();
			static void update();
			/**
			 * \brief Add and draw the MonoBehaviour from scene. 
			 * (I use reference instead of pointer because the pointer you use to create the MonoBehaviour might become null.
			 * And the MonoBehaviour should be able to remove from DisplayManager::childrens at any time.)
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
			// don't really know why I can't push a const GameObject& inside if
			// I type const GameObject& here :( ?
			static std::list<const GameObject*> childrens;
			static void draw_debug_collider(sf::RenderTarget& window, const GameObject* game_object);
		};
	}
}
#endif
