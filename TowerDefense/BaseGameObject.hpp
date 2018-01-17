#pragma once
#ifndef BASE_MONO_BEHAVIOUR_HPP
#define BASE_MONO_BEHAVIOUR_HPP
#include "GameObject.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		class BaseGameObject: public GameObject
		{
		public:
			BaseGameObject();
			~BaseGameObject();
			/**
			 * \brief Do `init(); Scene::addChild(*this); start();` in this order.
			 * For lazy peoples.
			 */
			void auto_start();
			/// Initialize variables
			virtual void init();
			/// Start BaseMonoBehaviour, called by the one instanciating him. You need to call base.start().
			virtual void start();
		protected:
			virtual void listenToEvents(); 
			virtual void unListenToEvents();
			/// Called every frame.
			virtual void update();
			/// Reset state (for pooling).
			virtual void recycle();
			/// Called by decontructor.
			virtual void onDestroy();
		private:
			bool flag_is_init;
		};

	}
}
#endif

