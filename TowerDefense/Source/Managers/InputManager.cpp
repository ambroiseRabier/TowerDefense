#include "stdafx.h"
#include "InputManager.hpp"
#include "Managers/GameManager.hpp"
#include "GameEngine/Physics.hpp"
#include "Constants.hpp"

using namespace sf;
using namespace TowerDefense::GameEngine;

namespace TowerDefense
{
	namespace Managers
	{
		void InputManager::init()
		{
		}
		// todo: having manager doing engine stuff do not seem correct
		void InputManager::update_mouse_btn_pressed(const sf::Event& event, const Window& window)
		{
        	if (Mouse::isButtonPressed(Mouse::Right))
			{
				Physics::on_right_click();
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				Physics::on_left_click();
			}
		}

		void InputManager::update(Window& window)
		{
			// Handle events
			Event event;
			while (window.pollEvent(event))
			{
				// Window closed or escape key pressed: exit
				if (event.type == Event::Closed 
					|| (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				{
					GlobalShared::on_window_close();
					window.close();
					break;
				}
				if (event.type == Event::KeyPressed)
				{
					switch (GameManager::state)
					{
						case GameState::Menu: update_menu_events(event); break;
						case GameState::Playing: update_playing_events(event); break;
						case GameState::Pause: update_pause_events(event); break;
					}
				}
				if (event.type == Event::MouseMoved)
				{
					// get relativ mouse position, always put before any Physics click
					// Mouse::getPosition() - window.getPosition(); give local position with offset of 30 on y because ou window top bar.
					Physics::mouse_position = Mouse::getPosition(window);
				}
				if (event.type == Event::MouseButtonPressed)
				{
					update_mouse_btn_pressed(event, window);
				}
			}
		}

		void InputManager::update_menu_events(const sf::Event& event)
		{
			switch (event.key.code)
			{
			// no break in case of two key.code ?
			case Keyboard::Return: GameManager::start_level(0);
			}
		}

		void InputManager::update_playing_events(const Event& event)
		{
			switch (event.key.code)
			{
			// no break in case of two key.code ?
			case Keyboard::R: GameManager::restart_level();
			case Keyboard::P: GameManager::pause();
			}
		}

		void InputManager::update_pause_events(const sf::Event& event)
		{
			switch (event.key.code)
			{
			// no break in case of two key.code ?
			case Keyboard::R: GameManager::restart_level();
			case Keyboard::P: GameManager::un_pause();
			}
		}
	}
}
