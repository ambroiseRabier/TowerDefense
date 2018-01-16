#include "stdafx.h"
#include "Managers/GameManager.hpp"
#include "Managers/UIManager.hpp"
#include "../TowerDefense/MonoBehaviour.hpp"
#include "../TowerDefense/Scene.hpp"

using namespace TowerDefense::Managers;
using namespace TowerDefense::GameEngine;

void displayLoading(sf::Texture& texture, sf::Sprite& loading_sprite, sf::RenderTarget& window)
{
	// Declare and load a texture
	// todo: add credits too !
	texture.loadFromFile("Assets/loading_background_inverted.png");
	// Create a sprite
	loading_sprite.setTexture(texture);
	//loading_sprite.setTextureRect(sf::IntRect(30, 40, 374, 126));
	//loading_sprite.setColor(sf::Color(255, 255, 255, 200));
	loading_sprite.setPosition(window.getSize().x/2  - 374/2, window.getSize().y/2 - 126/2);
	window.clear();
	window.draw(loading_sprite);
}

/**
 * @author: ambroise
 * todo: Use singleton instead of static to fasten loadtime of application?
 */
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense");
	window.setFramerateLimit(144);
	// loading init
	sf::Texture texture;
	sf::Sprite loading_sprite;
	displayLoading(texture, loading_sprite, window);
	window.display();
	// end loading init

	UIManager::Init();
	GameManager::Init();
	Scene::init();
	// forget asynchrone setTimeout like js. Gonna be too hard.
	sf::Time creditLoadingDuration = sf::seconds(2.0f);
	sf::sleep(creditLoadingDuration);
	//sf::CircleShape shape(55.f);
	//shape.setFillColor(sf::Color::Green);
	//MonoBehaviour* mono = new MonoBehaviour(0, &shape);
	//Scene::add(*mono);

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
			UIManager::update();
        }
		window.clear();
		GameManager::update();
		Scene::render(window);
		/*window.draw(shape);

		// UIManager Update for animation UI if needed
		// Declare and load a texture
			sf::Texture texture;
			texture.loadFromFile("Assets/orange_btn.jpg");
			// Create a sprite
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
			sprite.setColor(sf::Color(255, 255, 255, 200));
			sprite.setPosition(100, 25);
			// Draw it
			window.draw(sprite);
		// Declare and load a texture
			texture.loadFromFile("Assets/orange_btn.jpg");
			// Create a sprite
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(10, 10, 50, 30));
			sprite.setColor(sf::Color(255, 255, 255, 200));
			sprite.setPosition(50, 50);
			// Draw it
			window.draw(sprite);*/

		window.display();
	}
	return 0;
}
