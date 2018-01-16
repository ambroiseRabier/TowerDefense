#include "BaseMonoBehaviour.hpp"
#include "Scene.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		BaseMonoBehaviour::BaseMonoBehaviour()//: MonoBehaviour() // euh, ya pas de base. ?
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
			//Scene::add(*this);
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
			//Scene::remove(*this);
			BaseMonoBehaviour::unListenToEvents();
			BaseMonoBehaviour::initVar();
		}

		void BaseMonoBehaviour::onDestroy()
		{
			//Scene::remove(*this);
			BaseMonoBehaviour::unListenToEvents();
		}
	}
}
