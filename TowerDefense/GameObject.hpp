#pragma once
#ifndef MONO_BEHAVIOUR_HPP
#define MONO_BEHAVIOUR_HPP
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include "Collider.hpp"

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

			friend bool operator==(const GameObject& lhs, const GameObject& rhs)
			{
				return lhs.transformable == rhs.transformable;
			}

			friend bool operator!=(const GameObject& lhs, const GameObject& rhs)
			{
				return !(lhs == rhs);
			}

		public:
			static bool compare_z_index(const GameObject* first, const GameObject* second);
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

			// 
			/**
			 * \brief A Sprite/Text/Shape/VertexArray.
			 * Using pointer instead of reference because it can be null. Check for null before using.
			 * \return 
			 */
			sf::Drawable* get_drawable() const;

			std::shared_ptr<Collider> get_collider() const;

			// region physics

			/**
			 * \brief ONLY called if you have a collider added in Physics.
			 * Called every frame.
			 */
			virtual void on_mouse_overlap();

			/**
			 * \brief ONLY called if you have a collider added in Physics.
			 * Called every frame.
			 * Only if it is the front object that overlap the mouse.
			 * Called after on_mouse_overlap.
			 */
			virtual void on_mouse_overlap_front();

			/**
			 * \brief When mouse click on it (ignore z-index).
			 */
			virtual void on_mouse_click(bool left);

			/**
			 * \brief When mouse click on it, and it is the first in z-index being clicked.
			 */
			virtual void on_mouse_click_front(bool left);

			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned int get_zIndex() const { return z_index; }

			/**
			 * \brief Scene draw loop will skip this gameobject if set to false;
			 */
			bool isVisible = true;
		protected:
			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned int z_index = 0;

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

			std::shared_ptr<Collider> collider;
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
