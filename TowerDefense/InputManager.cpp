#include "stdafx.h"
#include "InputManager.hpp"
#include "Debug.hpp"
#include "Managers/GameManager.hpp"
#include "Physics.hpp"
#include "BaseGameObject.hpp"

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
		void InputManager::update_mouse(const sf::Event& event, const Window& window)
		{
			// mouse 
			// get relativ mouse position, always put before any Physics click
			Physics::mouse_position = Mouse::getPosition() - window.getPosition();
        	
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
			// Handle events todo:: make an input manager
			Event event;
			while (window.pollEvent(event))
			{
				// Window closed or escape key pressed: exit
				if (event.type == Event::Closed 
					|| (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				{
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
				update_mouse(event, window);
			}
		}

		void InputManager::update_menu_events(const sf::Event& event)
		{
			switch (event.key.code)
			{
			// no break in case of two key.code ?
			case Keyboard::Return: GameManager::StartLevel(0);
			}
		}

		void InputManager::update_playing_events(const Event& event)
		{
			switch (event.key.code)
			{
			// no break in case of two key.code ?
			case Keyboard::R: GameManager::RestartLevel();
			case Keyboard::P: GameManager::pause();
			}
		}

		void InputManager::update_pause_events(const sf::Event& event)
		{
			switch (event.key.code)
			{
			// no break in case of two key.code ?
			case Keyboard::R: GameManager::RestartLevel();
			case Keyboard::P: GameManager::un_pause();
			}
		}
	}
}
