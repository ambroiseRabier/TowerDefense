#pragma once
#ifndef BASE_BUTTON_HPP
#define BASE_BUTTON_HPP
#include "BaseGameObject.hpp"

namespace TowerDefense
{
	namespace UI
	{
		class BaseButton:public GameEngine::BaseGameObject
		{
		public:
			void destroy() override;
		protected:
			void init() override;
		};
	}
}
#endif

