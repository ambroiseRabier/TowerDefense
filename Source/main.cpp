#include "Header.h"
#include "Managers/GameManager.h"
#include "Utils/Singleton.h"

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
	std::cout << "helloworld";

	LoggerSingleton::Instance()->closeLogFile("logFile.txt yes");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//float dt = clock.restart().asSeconds();
		// update et autre
		// gamemanager, singleton
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}
