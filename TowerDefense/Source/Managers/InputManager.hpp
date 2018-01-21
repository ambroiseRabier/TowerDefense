#pragma once
#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

namespace TowerDefense
{
	namespace Managers
	{
		/**
		 * \brief 
		 * Handle inputs and call methods from others Managers.
		 */
		class InputManager
		{
		public:
			static void init();
			static void update(sf::Window& window);
			static void update_menu_events(const sf::Event& event);
			static void update_playing_events(const sf::Event& event);
			static void update_pause_events(const sf::Event& event);
			static void update_mouse_btn_pressed(const sf::Event& event, const sf::Window& window);

		};
	}
}
#endif
