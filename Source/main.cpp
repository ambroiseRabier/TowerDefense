#include "stdafx.h"
#include "Managers/GameManager.hpp"
#include "Managers/UIManager.hpp"
#include "../TowerDefense/MonoBehaviour.hpp"
#include "../TowerDefense/Scene.hpp"
#include "../TowerDefense/Constants.h"


using namespace TowerDefense::Managers;
using namespace TowerDefense::GameEngine;
using namespace TowerDefense;
using namespace sf;

float getFPS(const Time& time) {
     return (1000000.0f / time.asMicroseconds());
}


void displayLoading(Texture& texture, Sprite& loading_sprite, RenderTarget& window)
{
	// Declare and load a texture
	// todo: add credits too !
	texture.loadFromFile(Constants::Assets::loading_background);
	// Create a sprite
	loading_sprite.setTexture(texture);
	//loading_sprite.setTextureRect(IntRect(30, 40, 374, 126));
	//loading_sprite.setColor(Color(255, 255, 255, 200));
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
	RenderWindow window(VideoMode(800, 600), Constants::game_name);
	window.setFramerateLimit(Constants::fps_limit);
	// loading init
	// alocating on heap since I won't need it after loading.
	std::unique_ptr<Texture> loading_texture = std::make_unique<Texture>();
	std::unique_ptr<Sprite> loading_sprite = std::make_unique<Sprite>();
	displayLoading(*loading_texture, *loading_sprite, window);
	window.display();

	//fps debug only
	// Declare and load a font
	Font font;
	font.loadFromFile(Constants::Assets::default_font);
	GlobalShared::default_font = &font;

	// Create a text
	Text fpsText("FPS", font);
	fpsText.setCharacterSize(30);
	fpsText.setStyle(Text::Bold);
	fpsText.setFillColor(Color::Red);
	fpsText.setOutlineColor(Color::Blue);

	// FPS counter working variables
	Clock fpsClock;
	unsigned int fps = 0;
	unsigned int frame_count = 0;

	// Confirm that all GlobalShared variable that should have been setted are setted
	assert(GlobalShared::default_font != nullptr);

	// Init all managers
	UIManager::Init();
	GameManager::Init();
	Scene::init();

	// wait a bit to see the loading/credit screen.
	// (forget asynchrone setTimeout like js. Gonna be too hard)
	Time creditLoadingDuration = seconds(2.0f);
	sleep(creditLoadingDuration);
	
	// delete loading/credit stuff
	loading_sprite.reset(nullptr);
	loading_texture.reset(nullptr);

	// open menu
	//todo

	//CircleShape shape(55.f);
	//shape.setFillColor(Color::Green);
	//MonoBehaviour* mono = new MonoBehaviour(0, &shape);
	//Scene::add(*mono);

	while (window.isOpen())
	{
		// Handle events
        Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if (event.type == Event::Closed)
            {
                window.close();
                break;
			}
			if (GameManager::state == GameState::Playing)
			{
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				{
					UIManager::OpenPause();
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
				{
					GameManager::RestartLevel();
				}				
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::R && event.key.code == Keyboard::LControl)
				{
					GameManager::StartLevel(0);
				}
			}
			UIManager::update();
        }
		window.clear();
		GameManager::update();
		Scene::render(window);

		if(fpsClock.getElapsedTime().asSeconds() >= 1.f)
		{
			fps = frame_count;
			frame_count = 0;
			fpsClock.restart();
		}
 
		++frame_count;
		
		fpsText.setString(std::to_string(
			// prefer the long way of doing it instead of this shortcut, the fps displayed is more stable.
			//static_cast<int>(std::floor(getFPS(fpsClock.restart())))
			fps
		));
		window.draw(fpsText);
		/*window.draw(shape);

		// UIManager Update for animation UI if needed
		// Declare and load a texture
			Texture texture;
			texture.loadFromFile("Assets/orange_btn.jpg");
			// Create a sprite
			Sprite sprite;
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(10, 10, 50, 30));
			sprite.setColor(Color(255, 255, 255, 200));
			sprite.setPosition(100, 25);
			// Draw it
			window.draw(sprite);
		// Declare and load a texture
			texture.loadFromFile("Assets/orange_btn.jpg");
			// Create a sprite
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(10, 10, 50, 30));
			sprite.setColor(Color(255, 255, 255, 200));
			sprite.setPosition(50, 50);
			// Draw it
			window.draw(sprite);*/

		window.display();
	}
	return 0;
}
