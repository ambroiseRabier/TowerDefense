#pragma once
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace TowerDefense
{
	namespace GameEngine
	{
		/// orignal name that I never took from another engine.
		class MonoBehaviour
		{
		public:
			/**
			 * \brief 
			 * \param newZIndex 0 to 999 included.
			 * \param newDrawable 
			 */
			MonoBehaviour(unsigned int newZIndex, sf::Drawable* newDrawable);
			virtual ~MonoBehaviour();
			sf::Transformable& get_transformable() const;
			sf::Drawable& get_drawable() const;
			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned int get_zIndex() const { return zIndex; };
		protected:
			/**
			 * \brief Equivalent to unity transform (2D only)
			 */
			sf::Transformable* transformable;
			/**
			 * \brief A Sprite/Text/Shape/VertexArray
			 * This is the graphic part.
			 */
			sf::Drawable* drawable;

			// mettre sur objet hitbox ?
			//Rect ou circle, bref struct ? MAth truc ? geometry, etc ?
			//bool hitBoxActive;
			//bool triggerMouse;
		private:
			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned const int zIndex = 0;
		};
	}
}
