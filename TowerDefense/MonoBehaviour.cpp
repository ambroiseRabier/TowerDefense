#include "MonoBehaviour.hpp"
#include "stdafx.h"

using namespace sf;

namespace TowerDefense
{
	namespace GameEngine
	{
		MonoBehaviour::MonoBehaviour(unsigned newZIndex = 0, Drawable* newDrawable = nullptr) : drawable(newDrawable), zIndex(newZIndex)
		{
			assert(zIndex <= 999);
			transformable = new Transformable();
		}

		MonoBehaviour::~MonoBehaviour()
		{
			delete transformable;
			transformable = nullptr;
			delete drawable;
			drawable = nullptr;
		}

		// region getter setter

		Transformable& MonoBehaviour::get_transformable() const
		{
			return *transformable;
		}

		Drawable& MonoBehaviour::get_drawable() const
		{
			return *drawable;
		}
	}
}
