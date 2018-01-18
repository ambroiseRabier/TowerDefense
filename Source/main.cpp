#include "stdafx.h"
#include "Managers/GameManager.hpp"
#include "../TowerDefense/GameObject.hpp"
#include "../TowerDefense/Scene.hpp"
#include "../TowerDefense/Constants.hpp"
#include "../TowerDefense/BaseButton.hpp"
#include "../TowerDefense/Debug.hpp"
#include "../TowerDefense/Physics.hpp"
#include "../TowerDefense/MenuBackground.hpp"
#include "../TowerDefense/InputManager.hpp"

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

void preloading() // todo factorize
{
	// allocate on heap since this will stay longer then the stack of this function
	// then copy pointer on GlobalShared
	Font* font = new Font();
	font->loadFromFile(Constants::Assets::default_font);
	GlobalShared::default_font = font;
	Texture* texture = new Texture();
	texture->loadFromFile(Constants::Assets::default_ui_btn);
	GlobalShared::default_ui_btn = texture;
	texture = new Texture();
	texture->loadFromFile(Constants::Assets::menu_background);
	GlobalShared::menu_background = texture;
}

/**
 * @author: ambroise
 * todo: Use singleton instead of static to fasten loadtime of application?
 */
int main()
{
	Debug::info("Application started.");
	RenderWindow window(VideoMode(800, 600), Constants::Config::game_name);
	window.setFramerateLimit(Constants::Config::fps_limit);
	// loading init
	// alocating on heap since I won't need it after loading.
	std::unique_ptr<Texture> loading_texture = std::make_unique<Texture>();
	std::unique_ptr<Sprite> loading_sprite = std::make_unique<Sprite>();
	displayLoading(*loading_texture, *loading_sprite, window);
	window.display();

	// preloading
	preloading();
	Debug::info("Preloading done.");

	//fps text (debug only)
	Text fpsText("FPS", *GlobalShared::default_font);
	fpsText.setCharacterSize(30);
	fpsText.setStyle(Text::Bold);
	fpsText.setFillColor(Color::Red);
	fpsText.setOutlineColor(Color::Blue);

	// FPS counter working variables
	Clock fpsClock;
	unsigned int fps = 0;
	unsigned int frame_count = 0;

	// Init all managers
	Scene::init();
	Physics::init(Constants::Config::tested_collisions);
	GameManager::Init();
	Debug::info("Managers inited.");

	// wait a bit to see the loading/credit screen.
	// (forget asynchrone setTimeout like js. Gonna be too hard)
	const Time creditLoadingDuration = seconds(Constants::Config::min_loading_duration);
	sleep(creditLoadingDuration);
	
	// delete loading/credit stuff
	loading_sprite.reset(nullptr);
	loading_texture.reset(nullptr);

	UI::BaseButton* base_button = new UI::BaseButton(); // you could also put it on the stack.
	base_button->get_transformable().setPosition(150,150);
	base_button->auto_start();
	UI::MenuBackground* menu_background = new UI::MenuBackground();
	menu_background->auto_start();
	//base_button->destroy();
	//delete base_button;
	//base_button = nullptr;

	while (window.isOpen())
	{
		InputManager::update(window);
		GameManager::update();
		// !! updating mouse click after update game logic will be one frame wrong
		// relatively to what the user experience, but let's deal with it.
		Physics::update();
		// window.clear() was originnnaly before any game logic, but,
		// if the game logic take time then the user might see the window blink.
		window.clear();
		Scene::render(window);

		// fps overlay
		if(fpsClock.getElapsedTime().asSeconds() >= 1.f)
		{
			fps = frame_count;
			frame_count = 0;
			fpsClock.restart();
		}
		++frame_count;
		fpsText.setString(std::to_string(
			// prefer the long way of doing it instead of this shortcut bellow, the fps displayed is more stable.
			//static_cast<int>(std::floor(getFPS(fpsClock.restart())))
			fps
		));
		window.draw(fpsText);
		window.display();
	}
	return 0;
}
