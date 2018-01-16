#include "BaseMonoBehaviour.hpp"

namespace TowerDefense
{
	namespace Utils
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
			BaseMonoBehaviour::unListenToEvents();
			BaseMonoBehaviour::initVar();
		}

		void BaseMonoBehaviour::onDestroy()
		{
			BaseMonoBehaviour::unListenToEvents();
		}
	}
}
