#pragma once
#ifndef BASE_MONO_BEHAVIOUR_HPP
#define BASE_MONO_BEHAVIOUR_HPP
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
			~BaseGameObject();
			/**
			 * \brief Do `init(); Scene::addChild(*this); Physics::addChild(*this); start();` in this order.
			 * addChild are being done only if you provided a drawable, collider.
			 * For lazy peoples.
			 * \param hasCollider (default:false)
			 * \param hasGraphic (default:true)
			 */
			void auto_start();
			/**
			 * \brief Initialize BaseGameObject variables.
			 */
			virtual void init();
			/**
			 * \brief Start BaseGameObject.
			 */
			virtual void start();
			/**
			 * \brief You should call it before deleting BaseGameObject from memory.
			 */
			virtual void destroy();
		protected:
			virtual void listenToEvents(); 
			virtual void unListenToEvents();
			/// Called every frame.
			virtual void update();
			/// Reset state (for pooling).
			virtual void recycle();
		private:
			bool flag_is_init;
			bool flag_is_destroyed;
		};

	}
}
#endif
