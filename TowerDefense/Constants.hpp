#pragma once
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include "Collider.hpp"
#include <SFML/Graphics/Font.hpp>

using namespace TowerDefense::GameEngine;
namespace TowerDefense
{
	namespace Constants
	{

		/**
		 * \brief Config for the game.
		 */
		namespace Config
		{
			const std::string game_name = "TowerDefense"; // if you change this, you probably need to change namespaces ;)
			const unsigned int fps_limit = 144;
			const float min_loading_duration = 2.0f;
			/**
			 * \brief Assigned at start to Physics::testedCollisions.
			 */
			const std::vector<std::pair<Collider::Tag, Collider::Tag>> tested_collisions = {
				std::make_pair(Collider::Tag::Minion, Collider::Tag::Castle),
				std::make_pair(Collider::Tag::Minion, Collider::Tag::TowerShoot)
			};
		}

		/**
		 * \brief Path of the assets (images, sounds, ...)
		 */
		namespace Assets
		{
			const std::string loading_background = "Assets/loading_background_inverted.png";
			const std::string default_ui_btn = "Assets/orange_btn.jpg";
			const std::string default_font = "Assets/Inconsolata-Regular.ttf";
		}

		/**
		 * \brief You should use them as guideline for z-index assignation to gameobjects.
		 * If you ever happen to think you might overlap on another range of z-index, just up max and add a bigger range.
		 */
		namespace ZIndex
		{
			const unsigned int background_start = 0;
			const unsigned int game_objects_start = 100;
			const unsigned int ui_start = 900;
			const unsigned int max = 999;
		}
	}
	/**
	 * \brief Texture, font, and other assets reference that I need trough the game many times, or that I want to preload.
	 * Guaranted to be setted at main before the Managers init.
	 */
	namespace GlobalShared
	{
		extern sf::Font* default_font;
		extern sf::Texture* default_ui_btn;
	}
}
#endif
