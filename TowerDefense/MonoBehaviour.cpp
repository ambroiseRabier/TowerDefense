#include "MonoBehaviour.hpp"
#include "stdafx.h"
#include "Debug.hpp"

using namespace sf;

namespace TowerDefense
{
	namespace GameEngine
	{
		MonoBehaviour::MonoBehaviour(std::unique_ptr<Drawable> newDrawable, unsigned int newZIndex) : z_index(newZIndex), drawableUnique(std::move(newDrawable))
		{
			constructor_internal_init(newZIndex);
		}

		MonoBehaviour::MonoBehaviour(const std::shared_ptr<Drawable>& newDrawable, unsigned int newZIndex) : z_index(newZIndex), drawableShared(std::move(newDrawable))
		{
			constructor_internal_init(newZIndex);
		}

		MonoBehaviour::MonoBehaviour(Drawable* newDrawable, unsigned int newZIndex) : drawableRaw(newDrawable), z_index(newZIndex)
		{
			constructor_internal_init(newZIndex);
		}

		MonoBehaviour::MonoBehaviour(unsigned int newZIndex) : z_index(newZIndex)
		{
			constructor_internal_init(newZIndex);
		}

		MonoBehaviour::~MonoBehaviour()
		{
			transformable.reset(nullptr);
			if (drawableUnique) drawableUnique.reset(nullptr);
			if (drawableShared) drawableShared.reset();
			if (drawableRaw)
			{
				delete drawableRaw;
				drawableRaw = nullptr;
			}
		}

		void MonoBehaviour::constructor_internal_init(unsigned int newZIndex)
		{
			// arbitrary limit of 999
			Debug::assert_m(newZIndex <= 999, "z_index should be inferior or egal to 999");
			transformable = std::make_unique<Transformable>();
		}

		// region getter setter

		Transformable& MonoBehaviour::get_transformable() const
		{
			return *transformable;
		}

		Drawable* MonoBehaviour::get_drawable() const
		{
			if (drawableRaw) return drawableRaw;
			else if (drawableUnique) return drawableUnique.get();
			else if (drawableShared) return drawableShared.get();
			else return nullptr;
		}

		void MonoBehaviour::set_drawable(std::unique_ptr<Drawable> newDrawableUnique)
		{
			drawableUnique = std::move(newDrawableUnique);
		}

		void MonoBehaviour::set_drawable(const std::shared_ptr<Drawable>& newDrawableShared)
		{
			drawableShared = newDrawableShared;
		}

		void MonoBehaviour::set_drawable(Drawable* newDrawableRaw)
		{
			drawableRaw = newDrawableRaw;
		}
	}
}
