#include "stdafx.h"
#include "GameObject.hpp"
#include "Debug.hpp"
#include "../../Config.hpp"

using namespace sf;

namespace TowerDefense
{
	namespace GameEngine
	{
		bool GameObject::compare_z_index (const GameObject& first, const GameObject& second)
		{
			return first.get_zIndex() < second.get_zIndex();
		}
		bool GameObject::compare_z_index_p (const GameObject* first, const GameObject* second)
		{
			return first->get_zIndex() < second->get_zIndex();
		}

		GameObject::GameObject(const std::shared_ptr<Drawable>& newDrawable, unsigned int newZIndex) : z_index(newZIndex)
		{
			set_drawable_internal(newDrawable);
			constructor_internal_init(newZIndex);
		}

		GameObject::GameObject(unsigned int newZIndex) : z_index(newZIndex)
		{
			constructor_internal_init(newZIndex);
		}

		GameObject::~GameObject()
		{
			transformable.reset(nullptr);
			if (!drawable_shared_list.empty())
			{
				for (auto && shared : drawable_shared_list)
				{
					shared.reset();
				} 
				drawable_shared_list.clear();
			}
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


		Transformable& GameObject::get_transformable() const
		{
			return *transformable;
		}

		Drawable* GameObject::get_drawable() const
		{
			if (drawable_shared_list.empty())
				return nullptr;
			return drawable_shared_list.front().get();
		}

		const std::list<std::shared_ptr<sf::Drawable>>& GameObject::get_drawable_list() const
		{
			return drawable_shared_list;
		}

		/*std::shared_ptr<const Drawable>&& GameObject::get_drawable_shared() const
		{
			Debug::warn("GameObject::get_drawable_shared() function never tested");
			return drawable_shared_list.front();
		}*/

		Transformable* GameObject::get_drawable_transformable() const
		{
			assert(get_drawable());
			const auto temp = dynamic_cast<Transformable*>(get_drawable());
			// if you use this function then you are sure the drawable has a transform.
			assert(temp);
			return dynamic_cast<Transformable*>(get_drawable());
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
			set_drawable_internal(newDrawableShared);
		}

		void GameObject::set_drawable(const std::shared_ptr<Sprite>& drawable)
		{
			set_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}

		void GameObject::set_drawable(const std::shared_ptr<RectangleShape>& drawable)
		{
			set_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}

		void GameObject::set_drawable(const std::shared_ptr<CircleShape>& drawable)
		{
			set_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}

		void GameObject::set_drawable(const std::shared_ptr<Text>& drawable)
		{
			set_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}


		void GameObject::add_drawable(const std::shared_ptr<Drawable>& newDrawableShared)
		{
			add_drawable_internal(newDrawableShared);
		}

		void GameObject::add_drawable(const std::shared_ptr<Sprite>& drawable)
		{
			add_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}

		void GameObject::add_drawable(const std::shared_ptr<RectangleShape>& drawable)
		{
			add_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}

		void GameObject::add_drawable(const std::shared_ptr<CircleShape>& drawable)
		{
			add_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}

		void GameObject::add_drawable(const std::shared_ptr<Text>& drawable)
		{
			add_drawable_internal(static_cast<std::shared_ptr<Drawable>>(drawable));
		}


		void GameObject::set_drawable_internal(const std::shared_ptr<Drawable>& newDrawableShared)
		{
			const bool was_empty = drawable_shared_list.empty();
			if (was_empty)
			{
				drawable_shared_list.push_back(newDrawableShared);
			} 
			else
			{
				// destroy drawable (if that's the last shared_ptr)
				drawable_shared_list.front().reset();
				// remove from list
				drawable_shared_list.pop_front();
				// emplace seems a bit more efficient/modern from what I've read.
				drawable_shared_list.emplace_front(newDrawableShared);
			}
		}

		void GameObject::add_drawable_internal(const std::shared_ptr<Drawable>& newDrawableShared)
		{
			drawable_shared_list.push_back(newDrawableShared);
		}
	}
}
