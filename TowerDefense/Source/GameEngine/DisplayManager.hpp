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
			static void init();
			/**
			 * \brief Add and draw the MonoBehaviour from scene. 
			 * (I use reference instead of pointer because the pointer you use to create the MonoBehaviour might become null.
			 * And the MonoBehaviour should be able to remove from DisplayManager::childrens at any time.)
			 * \param game_object 
			 */
			static void addChild(const GameObject& game_object);
			/**
			 * \brief Remove the MonoBehaviour from scene. (won't be draw anymore)
			 * \param game_object 
			 */
			static void remove_child(const GameObject& game_object);
						
			/**
			 * \brief Render with zIndex.
			 * \param window
			 */
			static void render(sf::RenderTarget& window);
		private:
			static std::list<const GameObject*> childrens;
			static void draw_debug_collider(sf::RenderTarget& window, const GameObject* game_object);
		};
	}
}
#endif
