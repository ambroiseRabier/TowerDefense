#pragma once
#ifndef MONO_BEHAVIOUR_HPP
#define MONO_BEHAVIOUR_HPP
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace TowerDefense
{
	namespace GameEngine
	{
		/**
		 * \brief 
		 * 
		 * Usage (unique_ptr):
		 * std::unique_ptr<CircleShape> shape = std::make_unique<CircleShape>(70.f);
		 * shape->setFillColor(Color::Red);
		 * // upcast to Drawable
		 * MonoBehaviour* mono = new MonoBehaviour(static_cast<std::unique_ptr<Drawable>>(std::move(shape)), 1);
		 * Scene::addChild(*mono);
		 * 
		 * Usage (shared_ptr):
		 * // todo
		 * 
		 * Usage (IF YOU KNOW WHAT YOU'R DOING):
		 * CircleShape shape2(55.f);
		 * shape2.setFillColor(Color::Green);
		 * MonoBehaviour* mono2 = new MonoBehaviour(&shape2, 2);
		 * Scene::addChild(*mono2);
		 * 
		 */
		class GameObject
		{
		public:
			/**
			 * \brief 
			 * \param newZIndex 0 to 999 included.
			 * \param newDrawable 
			 */
			GameObject(std::unique_ptr<sf::Drawable> newDrawable, unsigned int newZIndex = 0);

			/**
			 * \brief shared pointer for sharing Drawable, you might prefer using unique_ptr.
			 * \param newDrawable 
			 * \param newZIndex 
			 */
			GameObject(const std::shared_ptr<sf::Drawable>& newDrawable, unsigned int newZIndex = 0);
			
			/**
			 * \brief FOR EXAMPLE ONLY, DO NOT USE THIS;
			 * \param newDrawable 
			 * \param newZIndex 
			 */
			GameObject(sf::Drawable* newDrawable, unsigned int newZIndex = 0);

			/**
			 * \brief Create a MonoBehaviour with no graphic.
			 * \param newZIndex 
			 */
			GameObject(unsigned int newZIndex = 0);

			virtual ~GameObject();
			sf::Transformable& get_transformable() const;
			// using pointer instead of reference because it can be null. Check for null before using.
			/**
			 * \brief A Sprite/Text/Shape/VertexArray
			 * \return 
			 */
			sf::Drawable* get_drawable() const;

			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned int get_zIndex() const { return z_index; };
		protected:
			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned const int z_index = 0;

			/**
			 * \brief Equivalent to unity transform (2D only)
			 */
			std::unique_ptr<sf::Transformable> transformable;

			void set_drawable(std::unique_ptr<sf::Drawable> newDrawableUnique);
			void set_drawable(const std::shared_ptr<sf::Drawable>& newDrawableShared);
			/**
			 * \brief USE ONLY IF YOU KNOW WHAT YOU ARE DOING
			 * \param newDrawableRaw 
			 * \return 
			 */
			void set_drawable(sf::Drawable* newDrawableRaw);

			// mettre sur objet hitbox ?
			//Rect ou circle, bref struct ? MAth truc ? geometry, etc ?
			//bool hitBoxActive;
			//bool triggerMouse;
		private:
			void constructor_internal_init(unsigned int newZIndex);
			std::unique_ptr<sf::Drawable> drawableUnique;
			std::shared_ptr<sf::Drawable> drawableShared;
			/**
			 * \brief USE ONLY IF YOU KNOW WHAT YOU ARE DOING
			 * \param newDrawableRaw 
			 * \return 
			 */
			sf::Drawable* drawableRaw;
		};
	}
}
#endif
