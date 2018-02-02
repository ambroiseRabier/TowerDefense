#pragma once
#ifndef BASE_GAME_OBJECT_HPP
#define BASE_GAME_OBJECT_HPP
#include "GameObject.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		/**
		 * \brief 
		 * Example of useage:
		 * UI::BaseButton* base_button = new UI::BaseButton();
		 * base_button->get_transformable().setPosition(200,200);
		 * base_button->auto_start();
		 * base_button->destroy();
		 * delete base_button;
		 * base_button = nullptr;
		 */
		class BaseGameObject: public GameObject
		{
		public:
			BaseGameObject();
			virtual ~BaseGameObject();
			/**
			 * \brief Do `init(); Scene::addChild(*this); Physics::addChild(*this); start();` in this order.
			 * addChild are being done only if you provided a drawable, collider.
			 * For lazy peoples.
			 */
			void auto_start();
			/**
			 * \brief Initialize BaseGameObject variables.
			 * This can be called again after using recycle().
			 * You should put initialization of elements that might change later here.
			 * But avoid creating texture/drawable here if they won't change in the gameobject lifetime (pooling).
			 */
			virtual void init();
			/**
			 * \brief Start BaseGameObject.
			 */
			virtual void start();
		protected:

			/**
			 * \brief If set to false update and on_update_after_collision won't be called.
			 */
			bool update_active = true;

			/**
			 * \brief 
			 * Called every frame.
			 */
			virtual void update();
			virtual void update_after_collision();

			/**
			 * \brief 
			 * Reset state. (for pooling)
			 */
			virtual void recycle();

		private:

			/**
			 * \brief Wrapper for update, to not call update when !isActive or !update_active.
			 */
			void update_internal();
			void update_after_collision_internal();

			/**
			 * \brief Security to find if init is called two times.
			 */
			bool flag_is_init;

			/**
			 * \brief 
			 * Avoid callind destroy two time when some children in inheritance call it too.
			 * (Calling it two time do not make it crash)
			 */
			bool flag_is_started;
		};

	}
}
#endif

