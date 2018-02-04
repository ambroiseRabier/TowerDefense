#include "stdafx.h"
#include "GameObject.hpp"
#include "Debug.hpp"
#include "../../Config.hpp"

using namespace sf;

namespace TowerDefense
{
	namespace GameEngine
	{
		// static
		bool GameObject::compare_z_index (const GameObject& first, const GameObject& second)
		{
			return first.get_zIndex() < second.get_zIndex();
		}
		bool GameObject::compare_z_index_p (const GameObject* first, const GameObject* second)
		{
			return first->get_zIndex() < second->get_zIndex();
		}
		//end static

		GameObject::GameObject(const std::shared_ptr<Drawable>& newDrawable, unsigned int newZIndex) : z_index(newZIndex), drawable_shared(std::move(newDrawable))
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
			if (drawable_shared) 
				drawable_shared.reset();
			if (collider) 
				collider.reset();
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
			return drawable_shared.get();
		}

		Transformable* GameObject::get_drawable_transformable() const
		{
			const auto temp = dynamic_cast<Transformable*>(drawable_shared.get());
			// if you use this function then you are sure the drawable has a transform.
			assert(temp);
			return dynamic_cast<Transformable*>(drawable_shared.get());
		}

		std::shared_ptr<Collider> GameObject::get_collider() const
		{
			return collider;
		}

		void GameObject::on_mouse_overlap()
		{
		}

		void GameObject::on_mouse_overlap_front()
		{
		}

		void GameObject::on_mouse_click(bool left)
		{
		}

		void GameObject::on_mouse_click_front(bool left)
		{
		}

		void GameObject::on_game_object_overlap(GameObject& game_object)
		{
		}

		Vector2f GameObject::to_local(const sf::Vector2f& global_vector2) const
		{
			return Vector2f(
				global_vector2.x - transformable->getPosition().x,
				global_vector2.y - transformable->getPosition().y 
			);
		}

		void GameObject::set_drawable(const std::shared_ptr<Drawable>& newDrawableShared)
		{
			drawable_shared = newDrawableShared;
		}

		void GameObject::set_drawable(const std::shared_ptr<Sprite>& drawable)
		{
			drawable_shared = static_cast<std::shared_ptr<Drawable>>(drawable);
		}

		void GameObject::set_drawable(const std::shared_ptr<RectangleShape>& drawable)
		{
			drawable_shared = static_cast<std::shared_ptr<Drawable>>(drawable);
		}

		void GameObject::set_drawable(const std::shared_ptr<CircleShape>& drawable)
		{
			drawable_shared = static_cast<std::shared_ptr<Drawable>>(drawable);
		}

		void GameObject::set_drawable(const std::shared_ptr<Text>& drawable)
		{
			drawable_shared = static_cast<std::shared_ptr<Drawable>>(drawable);
		}
	}
}
