#pragma once
#ifndef ALIGN_HPP
#define ALIGN_HPP
#include "GameEngine/GameObject.hpp"

using namespace TowerDefense::GameEngine;
namespace TowerDefense
{
	namespace UI
	{
		class Align // todo: add surcharge to not use Vector2f but two arguments.
		{
		public:
			static void top(sf::Transformable& transformable, const float& offset=0.f);
			static void bottom(sf::Transformable& transformable, const float& offset=0.f);
			static void right(sf::Transformable& transformable, const float& offset=0.f);
			static void left(sf::Transformable& transformable, const float& offset=0.f);
			static void center(sf::Transformable& transformable, const sf::Vector2f& offset);
			static void top_left(sf::Transformable& transformable, const sf::Vector2f& offset);
			static void top_right(sf::Transformable& transformable, const sf::Vector2f& offset);
			static void bottom_left(sf::Transformable& transformable, const sf::Vector2f& offset);
			static void bottom_right(sf::Transformable& transformable, const sf::Vector2f& offset);
			static void top_center(sf::Transformable& transformable, const sf::Vector2f& offset);
			static void bottom_center(sf::Transformable& transformable, const sf::Vector2f& offset);

			// posbbilité pour aligner tout seul le prite, faire un get width et get height ds gameobject calculé automatiquement
			// à partir des sprite, shape, text qu'il contient, sachant qu'il peut en contenir plusieurs pas vertex array...
			// à partir de cet widht/height calculé l'offset nécessaire.

			// surcharge mvoe the gameobject transformalbe and sprite transformable 
			/*static void top(GameObject& game_object, const float& offset=0.f);
			static void bottom(GameObject& game_object, const float& offset=0.f);
			static void right(GameObject& game_object, const float& offset=0.f);
			static void left(GameObject& game_object, const float& offset=0.f);
			static void center(GameObject& game_object, const sf::Vector2f& offset);
			static void top_left(GameObject& game_object, const sf::Vector2f& offset);
			static void top_right(sf::Sprite& sprite, const sf::Vector2f& offset);
			static void bottom_left(GameObject& game_object, const sf::Vector2f& offset);
			static void bottom_right(GameObject& game_object, const sf::Vector2f& offset);
			static void top_center(GameObject& game_object, const sf::Vector2f& offset);
			static void bottom_center(GameObject& game_object, const sf::Vector2f& offset);*/
		};
	}
}
#endif
