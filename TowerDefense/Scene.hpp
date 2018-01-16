#pragma once
#include "Utils/Singleton.hpp"


namespace TowerDefense
{
	namespace Utils
	{
		class SceneInternal
		{
		public:
			SceneInternal();
			~SceneInternal();
			//void AddToScene( Trans);
			typedef Singleton<SceneInternal> Scene; // global declaration
		};
	}
}
