#include "BaseMonoBehaviour.hpp"
#include "Scene.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		BaseMonoBehaviour::BaseMonoBehaviour()
		{
			BaseMonoBehaviour::awake();
		}

		BaseMonoBehaviour::~BaseMonoBehaviour()
		{
			BaseMonoBehaviour::onDestroy();
		}

		void BaseMonoBehaviour::awake()
		{
			BaseMonoBehaviour::initVar();
		}

		void BaseMonoBehaviour::initVar()
		{
			
		}

		void BaseMonoBehaviour::start()
		{
			BaseMonoBehaviour::listenToEvents();
			// It is better if oyu addchild them yourselve
			//Scene::addChild(*this);
		}

		void BaseMonoBehaviour::listenToEvents()
		{
			
		}

		void BaseMonoBehaviour::unListenToEvents()
		{
			
		}

		void BaseMonoBehaviour::update()
		{
			
		}

		void BaseMonoBehaviour::recycle()
		{
			// remove from scene in case removechildre has been forgotten
			Scene::removeChild(*this);
			BaseMonoBehaviour::unListenToEvents();
			BaseMonoBehaviour::initVar();
		}

		void BaseMonoBehaviour::onDestroy()
		{
			// remove from scene in case removechildre has been forgotten
			Scene::removeChild(*this);
			BaseMonoBehaviour::unListenToEvents();
		}
	}
}
