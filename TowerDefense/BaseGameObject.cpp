#include "BaseGameObject.hpp"
#include "Scene.hpp"
#include "Debug.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		BaseGameObject::BaseGameObject()
		{
		}

		BaseGameObject::~BaseGameObject()
		{
			BaseGameObject::onDestroy();
		}

		void BaseGameObject::auto_start()
		{
			init();
			Scene::addChild(*this);
			start();
		}

		void BaseGameObject::init()
		{
			flag_is_init = true;
			Debug::log("bgm initvar");
		}

		void BaseGameObject::start()
		{
			Debug::assert_m(flag_is_init, "BaseGameObject: Call init() before calling start().");
			listenToEvents();
			// It is better if oyu addchild them yourselve
			//Scene::addChild(*this);
		}

		void BaseGameObject::listenToEvents()
		{
			
		}

		void BaseGameObject::unListenToEvents()
		{
			
		}

		void BaseGameObject::update()
		{
			
		}

		void BaseGameObject::recycle()
		{
			// remove from scene in case removechildre has been forgotten
			Scene::removeChild(*this);
			unListenToEvents();
			init();
		}

		void BaseGameObject::onDestroy()
		{
			Debug::log("bgm onDestroy");
			// remove from scene in case removechildre has been forgotten
			Scene::removeChild(*this);
			unListenToEvents();
		}
	}
}
