#pragma once
#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP
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
			static void init(sf::RenderWindow& new_window_ref);
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
			static unsigned int get_width();
			static unsigned int get_height();
		private:
			static std::list<const GameObject*> childrens;
			static sf::RenderWindow* window_ref;
			static void draw_debug_collider(sf::RenderTarget& window, const GameObject* game_object);
		};
	}
}
#endif
