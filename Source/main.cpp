#include "stdafx.h"
#include "Managers/GameManager.hpp"
#include "Managers/UIManager.hpp"
#include <iomanip>

using namespace TowerDefense::Managers;

/**
 * @author: ambroise
 * Organizing VS C++ folders : https://stackoverflow.com/questions/5321404/vc2010-c-organizing-source-files/5323140#5323140
 * https://stackoverflow.com/questions/7878703/keep-source-files-in-an-external-directory-in-visual-studio-c
 */
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense");
	window.setFramerateLimit(144);
	sf::CircleShape shape(55.f);
	shape.setFillColor(sf::Color::Green);

	UIManager::Init();
	GameManager::Init();
	while (window.isOpen())
	{
		// Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
			}
			if (GameManager::state == GameState::Playing)
			{
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				{
					UIManager::OpenPause();
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
				{
					GameManager::RestartLevel();
				}				
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && event.key.code == sf::Keyboard::LControl)
				{
					GameManager::StartLevel(0);
				}
			}
			UIManager::Update();
        }
		window.clear();
		GameManager::Update();
		std::cout << GameManager::get_deltaTime();
		// UIManager Update for animation UI if needed

		window.draw(shape);
		window.display();
	}
	return 0;
}
