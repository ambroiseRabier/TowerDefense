#include "GameObject.hpp"
#include "stdafx.h"
#include "Debug.hpp"
#include "Constants.hpp"

using namespace sf;

namespace TowerDefense
{
	namespace GameEngine
	{
		// static
		bool GameObject::compare_z_index (const GameObject* first, const GameObject* second)
		{
			return first->get_zIndex() < second->get_zIndex();
		}

		GameObject::GameObject(std::unique_ptr<Drawable> newDrawable, unsigned int newZIndex) : z_index(newZIndex), drawableUnique(std::move(newDrawable))
		{
			constructor_internal_init(newZIndex);
		}

		GameObject::GameObject(const std::shared_ptr<Drawable>& newDrawable, unsigned int newZIndex) : z_index(newZIndex), drawableShared(std::move(newDrawable))
		{
			constructor_internal_init(newZIndex);
		}

		GameObject::GameObject(Drawable* newDrawable, unsigned int newZIndex) : drawableRaw(newDrawable), z_index(newZIndex)
		{
			constructor_internal_init(newZIndex);
		}

		GameObject::GameObject(unsigned int newZIndex) : z_index(newZIndex)
		{
			constructor_internal_init(newZIndex);
		}

		GameObject::~GameObject()
		{
			transformable.reset(nullptr);
			// smartpointer should be explicitely cast to bool, even if Resharper is not ok.
			if (drawableUnique.get()) drawableUnique.reset(nullptr);
			if (drawableShared.get()) drawableShared.reset();
			if (drawableRaw)
			{
				delete drawableRaw;
				drawableRaw = nullptr;
			}
			if (collider) collider.reset();
		}

		void GameObject::constructor_internal_init(unsigned int newZIndex)
		{
			// arbitrary limit of zIndex
			Debug::assert_m(
				newZIndex <= Constants::ZIndex::max, 
				"z_index should be inferior or egal to " + std::to_string(Constants::ZIndex::max)
			);
			transformable = std::make_unique<Transformable>();
		}

		// region getter setter

		Transformable& GameObject::get_transformable() const
		{
			return *transformable;
		}

		Drawable* GameObject::get_drawable() const
		{
			if (drawableRaw) return drawableRaw;
			else if (drawableUnique) return drawableUnique.get();
			else if (drawableShared) return drawableShared.get();
			else return nullptr;
		}

		std::shared_ptr<Collider> GameObject::get_collider() const
		{
			return collider;
		}

		void GameObject::set_drawable(std::unique_ptr<Drawable> newDrawableUnique)
		{
			drawableUnique = std::move(newDrawableUnique);
		}

		void GameObject::set_drawable(const std::shared_ptr<Drawable>& newDrawableShared)
		{
			drawableShared = newDrawableShared;
		}

		void GameObject::set_drawable(Drawable* newDrawableRaw)
		{
			drawableRaw = newDrawableRaw;
		}
	}
}
