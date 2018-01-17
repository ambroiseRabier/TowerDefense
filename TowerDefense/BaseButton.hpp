#pragma once
#ifndef BASE_BUTTON_HPP
#define BASE_BUTTON_HPP
#include "BaseMonoBehaviour.hpp"

namespace TowerDefense
{
	namespace UI
	{
		class BaseButton:public GameEngine::BaseMonoBehaviour
		{
		protected:
			void initVar() override;
		};
	}
}
#endif

