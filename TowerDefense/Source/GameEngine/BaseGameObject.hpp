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
			~BaseGameObject();
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
			virtual void listenToEvents(); 
			virtual void unListenToEvents();

			/**
			 * \brief 
			 * Called every frame.
			 */
			virtual void update();
			
			/**
			 * \brief 
			 * Reset state. (for pooling)
			 */
			virtual void recycle();

			
			/**
			 * \brief
			 * It is called in descontructor (no manual public call since alt-f4, pressing red creutz would not call it).
			 * You cannot call virtual children methods in deconstructor.
			 * That mean the override of unlistenEvents() IS NOT CALLED if you call destroy() in deconstructor of BaseGameObject.
			 * (same for destroy() override)
			 * BUT if you call destroy() in BaseButton (as exemple) that inherit from BaseGameObject then BaseGameObject destroy() will be called.
			 * 
			 * If you want your override of destroy and unlistenToEvents to work you need to call destroy() from your own deconstructor.
			 */
			virtual void destroy();
		private:
			bool flag_is_init;
			/**
			 * \brief 
			 * Avoid callind destroy two time when some children in inheritance call it too.
			 * (Calling it two time do not make it crash)
			 */
			bool flag_is_destroyed;
		};

	}
}
#endif

