#include "stdafx.h"
#include "Managers/GameManager.hpp"
#include "GameEngine/Debug.hpp"
#include "GameEngine/DisplayManager.hpp"
#include "GameEngine/CollisionManager.hpp"
#include "Managers/InputManager.hpp"
#include "../MenuScreen.hpp"
#include "../Hud.hpp"
#include "../PauseScreen.hpp"
#include "../UIAssets.hpp"
#include "../GlobalShared.hpp"
#include "../Config.hpp"
#include "../MapManager.hpp"
#include "../Timer.hpp"
#include "../MapWaveManager.hpp"
#include "../Destroyer.hpp"
#include "../Player.hpp"
#include "../GameOverScreen.hpp"
#include "../GameWinScreen.hpp"
#include "../GameClearedScreen.hpp"
#include "../SoundManager.hpp"

using namespace TowerDefense::Managers;
using namespace TowerDefense::GameEngine;
using namespace TowerDefense::Constants;
using namespace TowerDefense;
using namespace sf;


void displayLoading(Texture& texture, Sprite& loading_sprite, RenderTarget& window)
{
	// Declare and load a texture
	// todo: add credits too !
	texture.loadFromFile(UIAssets::loading_background);
	// Create a sprite
	loading_sprite.setTexture(texture);
	//loading_sprite.setTextureRect(IntRect(30, 40, 374, 126));
	//loading_sprite.setColor(Color(255, 255, 255, 200));
	loading_sprite.setPosition(window.getSize().x/2  - 374.0f/2.0f, window.getSize().y/2 - 126.0f/2.0f);
	window.clear();
	window.draw(loading_sprite);
}

/**
 * @author: Ambroise Rabier
 */
int main()
{
	Debug::info("Application started.");
	// help find memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//system("pause");
	RenderWindow window(
		VideoMode(Config::window_width, Config::window_height),
		Config::game_name,
		Style::Default, 
		// ReSharper disable once CppRedundantQualifier
		sf::ContextSettings(
			0,
			0,
			4, // anti-aliasing
			2,
			0 
		)
	);
	window.setFramerateLimit(Config::fps_limit);
	// loading init
	// alocating on heap since I won't need it after loading.
	std::unique_ptr<Texture> loading_texture = std::make_unique<Texture>();
	std::unique_ptr<Sprite> loading_sprite = std::make_unique<Sprite>();
	displayLoading(*loading_texture, *loading_sprite, window);
	window.display();

	// preloading
	GlobalShared::load_all_fonts();
	GlobalShared::load_all_textures();
	GlobalShared::load_all_sounds();
	Debug::info("Preloading done.");
	
	// Init all managers
	Debug::init();
	Utils::Timer::init();
	DisplayManager::init();
	CollisionManager::init(Config::tested_collisions);
	Destroyer::init();
	SoundManager::init();
	Player::init();
	MapManager::init();
	MapWaveManager::init();
	UI::MenuScreen::init();
	UI::Hud::init();
	UI::PauseScreen::init();
	UI::GameWinScreen::init();
	UI::GameOverScreen::init();
	UI::GameClearedScreen::init();
	GameManager::init(&window);
	Debug::info("Managers inited.");

	// delete loading/credit stuff because we don't need it anymore
	// note: since this is smartpointers, they destroy themselves when out of stack.
	loading_sprite.reset(nullptr);
	loading_texture.reset(nullptr);

	// start the game !
	GameManager::start();
	Debug::info("Game started.");

	while (window.isOpen())
	{
		InputManager::update(window);
		Utils::Timer::update();
		GameManager::update();
		// !! updating mouse click after update game logic will be one frame wrong
		// relatively to what the user experience, but let's deal with it.
		CollisionManager::update();
		GameManager::update_after_collision();
		// window.clear() was originnnaly before any game logic, but,
		// if the game logic take time then the user might see the window blink.
		Destroyer::update();
		window.clear();
		DisplayManager::render(window);
		Debug::update(window);
		window.display();
	}
	// destroying the quit_btn NOT when the quit_btn fire en click event avoid a null iterator problem.
	UI::MenuScreen::destroy_quit_btn();
	// destroy any global here.
	GlobalShared::destroy();
	Debug::destroy();
	// do not use this, it take static variable as false positiv.
	//_CrtDumpMemoryLeaks(); 
	//system("pause");
	return 0;
}
