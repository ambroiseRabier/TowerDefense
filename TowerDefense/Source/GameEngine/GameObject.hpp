#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include "Collider.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		/**
		 * \brief 
		 * 
		 * Usage (unique_ptr):
		 * std::shared_ptr<CircleShape> shape = std::make_shared<CircleShape>(70.f);
		 * shape->setFillColor(Color::Red);
		 * // upcast to Drawable
		 * MonoBehaviour* mono = new MonoBehaviour(static_cast<std::shared_ptr<Drawable>>(std::move(shape)), 1);
		 * DisplayManager::addChild(*mono);
		 * 
		 */
		class GameObject
		{
		private:
			friend bool operator==(const GameObject& lhs, const GameObject& rhs)
			{
				return lhs.transformable == rhs.transformable;
			}

			friend bool operator!=(const GameObject& lhs, const GameObject& rhs)
			{
				return !(lhs == rhs);
			}

		public:
			static bool compare_z_index(const GameObject& first, const GameObject& second);
			static bool compare_z_index_p(const GameObject* first, const GameObject* second);

			/**
			 * \brief 
			 * \param newDrawable 
			 * \param newZIndex 
			 */
			GameObject(const std::shared_ptr<sf::Drawable>& newDrawable, unsigned int newZIndex = 0);

			/**
			 * \brief Create a MonoBehaviour with no graphic.
			 * This is also the default constructor used by BaseGameObjects.
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
			const std::list<std::shared_ptr<sf::Drawable>>& get_drawable_list() const;

			/**
			 * \brief 
			 * Wait what ? Drawable do not have a transformable !
			 * Exactly ! And in my opinion having multiple inheritance for sprite/shape/text,vertexarray
			 * is an design error. Yes ! Because I either need to keep reference of:
			 * - drawable and transformable
			 * or
			 * - sprite,shape,text,vertexarray
			 * And there is no common unique inheritance for those four last.
			 * So I choose the first solution.
			 */
			sf::Transformable* get_drawable_transformable() const;


			std::shared_ptr<Collider> get_collider() const;

			// region physics

			/**
			 * \brief ONLY called if you have a collider added in CollisionManager.
			 * Called every frame.
			 */
			virtual void on_mouse_overlap();

			/**
			 * \brief ONLY called if you have a collider added in CollisionManager.
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

			virtual void on_game_object_overlap(GameObject& game_object);

			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned int get_zIndex() const { return z_index; }

			/**
			 * \brief DisplayManager draw loop will skip this gameobject if set to false;
			 */
			bool isVisible = true;

			/**
			 * \brief If isActive is false, it won't be displayed or do any collision or events.
			 */
			bool isActive = true;

			sf::Vector2f to_local(const sf::Vector2f&) const;
		protected:
			/**
			 * \brief Is rendered from 0 to 999 included.
			 */
			unsigned int z_index = 0;

			/**
			 * \brief Equivalent to unity transform (2D only)
			 */
			std::unique_ptr<sf::Transformable> transformable;

			void set_drawable(const std::shared_ptr<sf::Drawable>& newDrawableShared);
			void set_drawable(const std::shared_ptr<sf::Sprite>& drawable);
			void set_drawable(const std::shared_ptr<sf::RectangleShape>& drawable);
			void set_drawable(const std::shared_ptr<sf::CircleShape>& drawable);
			void set_drawable(const std::shared_ptr<sf::Text>& drawable);

			void add_drawable(const std::shared_ptr<sf::Drawable>& newDrawableShared);
			void add_drawable(const std::shared_ptr<sf::Sprite>& drawable);
			void add_drawable(const std::shared_ptr<sf::RectangleShape>& drawable);
			void add_drawable(const std::shared_ptr<sf::CircleShape>& drawable);
			void add_drawable(const std::shared_ptr<sf::Text>& drawable);

			std::shared_ptr<Collider> collider;
			// mettre sur objet hitbox ?
			//Rect ou circle, bref struct ? MAth truc ? geometry, etc ?
			//bool hitBoxActive;
			//bool triggerMouse;
			
			/**
			 * \brief First value is drawable_shared
			 */
			std::list<std::shared_ptr<sf::Drawable>> drawable_shared_list;
		private:
			void constructor_internal_init(unsigned int newZIndex);
			void set_drawable_internal(const std::shared_ptr<sf::Drawable>& newDrawableShared);
			void add_drawable_internal(const std::shared_ptr<sf::Drawable>& newDrawableShared);

		};
	}
}
#endif
