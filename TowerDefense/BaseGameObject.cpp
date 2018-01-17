#include "BaseGameObject.hpp"
#include "Scene.hpp"
#include "Debug.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		BaseGameObject::BaseGameObject()
		{
			BaseGameObject::awake();
		}

		BaseGameObject::~BaseGameObject()
		{
			BaseGameObject::onDestroy();
		}

		void BaseGameObject::awake()
		{
			Debug::log("bgm awake");
			BaseGameObject::initVar();
		}

		void BaseGameObject::initVar()
		{
			Debug::log("bgm initvar");
		}

		void BaseGameObject::start()
		{
			BaseGameObject::listenToEvents();
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
			BaseGameObject::unListenToEvents();
			BaseGameObject::initVar();
		}

		void BaseGameObject::onDestroy()
		{
			// remove from scene in case removechildre has been forgotten
			Scene::removeChild(*this);
			BaseGameObject::unListenToEvents();
		}
	}
}
