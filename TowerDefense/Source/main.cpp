#include "stdafx.h"
#include "Managers/GameManager.hpp"
#include "GameEngine/Debug.hpp"
#include "GameEngine/Scene.hpp"
#include "GameEngine/Physics.hpp"
#include "Managers/InputManager.hpp"
#include "../MenuScreen.hpp"
#include "../Hud.hpp"
#include "../PauseScreen.hpp"
#include "../Assets.hpp"
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

using namespace TowerDefense::Managers;
using namespace TowerDefense::GameEngine;
using namespace TowerDefense::Constants;
using namespace TowerDefense;
using namespace sf;

float getFPS(const Time& time) {
     return (1000000.0f / time.asMicroseconds());
}

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
	GlobalShared::load_all_textures();
	// allocate on heap since this will stay longer then the stack of this function
	// then copy pointer on GlobalShared
	Font* font = DBG_NEW Font();
	font->loadFromFile(Assets::default_font);
	GlobalShared::default_font = font;
	Debug::info("Preloading done.");

	//fps text (debug only)
	Text fpsText("*FPS", *GlobalShared::default_font);
	fpsText.setCharacterSize(30);
	fpsText.setStyle(Text::Bold);
	fpsText.setFillColor(Color::Red);
	fpsText.setOutlineColor(Color::Blue);

	// FPS counter working variables
	Clock fpsClock;
	unsigned int fps = 0;
	unsigned int frame_count = 0;
	
	// Init all managers
	Utils::Timer::init();
	Scene::init();
	Physics::init(Config::tested_collisions);
	Destroyer::init();
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

	// exemples stuff, to delete.
	//UI::BaseButton* base_button = new UI::BaseButton(); // you could also put it on the stack.
	//base_button->get_transformable().setPosition(150,150);
	//base_button->auto_start();

	//std::unique_ptr<UI::BaseButton> base_button_unique = std::make_unique<UI::BaseButton>();
	//base_button_unique->auto_start();

	//UI::MenuBackground* menu_background = new UI::MenuBackground();
	//menu_background->auto_start();
	////base_button->destroy();
	//delete base_button;
	//base_button = nullptr;
	//delete menu_background;
	//base_button = nullptr;
	//base_button_unique.reset(nullptr);

	while (window.isOpen())
	{
		InputManager::update(window);
		Utils::Timer::update();
		GameManager::update();
		// !! updating mouse click after update game logic will be one frame wrong
		// relatively to what the user experience, but let's deal with it.
		Physics::update();
		GameManager::update_after_collision();
		// window.clear() was originnnaly before any game logic, but,
		// if the game logic take time then the user might see the window blink.
		Destroyer::update();
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
	// destroying the quit_btn NOT when the quit_btn fire en click event avoid a null iterator problem.
	UI::MenuScreen::destroy_quit_btn();
	// destroy any global here.
	GlobalShared::destroy();

	// do not use this, it take static variable as false positiv.
	//_CrtDumpMemoryLeaks(); 
	//system("pause");
	return 0;
}
