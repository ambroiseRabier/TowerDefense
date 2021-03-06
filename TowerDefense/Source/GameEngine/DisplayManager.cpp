#include "stdafx.h"
#include "DisplayManager.hpp"
#include "Debug.hpp"
#include "CollisionManager.hpp"
#include "../../Config.hpp"
#include "../../GlobalShared.hpp"

using namespace std;
namespace TowerDefense
{
	namespace GameEngine
	{
		std::list<const GameObject*> DisplayManager::childrens;
		sf::RenderWindow* DisplayManager::window_ref;

		void DisplayManager::init(sf::RenderWindow& new_window_ref)
		{
			window_ref = &new_window_ref;
		}

		void DisplayManager::addChild(const GameObject& game_object)
		{
			const bool allready_exit = std::find(childrens.begin(), childrens.end(), &game_object) != childrens.end();
			if (!allready_exit)
			{
				Debug::assert_m((&game_object)->get_drawable(), "DisplayManager: A gameobject you add to the scene should have a drawable setted.");
				childrens.push_back(&game_object);
			}
			else
			{
				Debug::warn("DisplayManager: The element you are trying to push on scene is already on the scene.");
			}
		}

		void DisplayManager::remove_child(const GameObject& game_object)
		{
			// can be empty when exiting application.
			if (!childrens.empty())
			{
				childrens.remove(&game_object);
			}
		}

		void DisplayManager::render(sf::RenderTarget& window)
		{
			childrens.sort(GameObject::compare_z_index_p);
			for (const GameObject* children : childrens)
			{
				// well, you could remove the drawable without error, but that is not encouraged.
				// get_drawable also check that the drawable list is not empty.
				if (children->isVisible && children->isActive && children->get_drawable())
				{
					// combine GameObject "transform" to the GameObject "graphic"
					for (auto&& drawable : children->get_drawable_list())
					{
						window.draw(
							*drawable.get(),
							children->get_transformable().getTransform()
						);
					}

					// ReSharper disable once CppRedundantBooleanExpressionArgument
					if (GlobalShared::get_config().debug_draw_collider && children->get_collider())
					{
						draw_debug_collider(window, children);
					}
				}
			}
		}

		unsigned int DisplayManager::get_width()
		{
			return window_ref->getSize().x;
		}

		unsigned int DisplayManager::get_height()
		{
			return window_ref->getSize().y;
		}

		void DisplayManager::draw_debug_collider(sf::RenderTarget& window, const GameObject* game_object)
		{
			if (game_object->get_collider()->get_type() == Collider::Type::Rect)
			{
				// stack
				sf::RectangleShape rc = sf::RectangleShape(
					sf::Vector2f(
						game_object->get_collider()->get_rect().width,
						game_object->get_collider()->get_rect().height
					)
				);
				rc.setPosition(
					game_object->get_collider()->get_rect().left,
					game_object->get_collider()->get_rect().top
				);
				//rc.setTexture(GlobalShared::collider_debug_texture); // cannot use texture and color it seems :/
				rc.setFillColor(Constants::Config::collider_debug_color);
				rc.setOutlineColor(sf::Color::Red);
				rc.setOutlineThickness(1.0f);
				window.draw(
					rc,
					game_object->get_transformable().getTransform()
				);
			} 
			else if (game_object->get_collider()->get_type() == Collider::Type::Circle)
			{
				// stack
				sf::CircleShape circle = sf::CircleShape(
					game_object->get_collider()->get_circle().radius
				);
				// the circle origin is top left...
				circle.setPosition(
					game_object->get_collider()->get_circle().position.x - game_object->get_collider()->get_circle().radius,
					game_object->get_collider()->get_circle().position.y - game_object->get_collider()->get_circle().radius
				);
				//rc.setTexture(GlobalShared::collider_debug_texture); // cannot use texture and color it seems :/
				circle.setFillColor(Constants::Config::collider_debug_color);
				circle.setOutlineColor(sf::Color::Red);
				circle.setOutlineThickness(1.0f);
				window.draw(
					circle,
					game_object->get_transformable().getTransform()
				);
			}
			else if (game_object->get_collider()->get_type() == Collider::Type::Dot)
			{
				// stack
				sf::RectangleShape rect = sf::RectangleShape(
					sf::Vector2f(
						// one pixel.
						1.f,
						1.f
					)
				);
				// the circle origin is top left...
				rect.setPosition(
					game_object->get_collider()->get_dot()
				);
				//rc.setTexture(GlobalShared::collider_debug_texture); // cannot use texture and color it seems :/
				rect.setFillColor(sf::Color::Red);
				window.draw(
					rect,
					game_object->get_transformable().getTransform()
				);
			}
			else
			{
				Debug::warn(
					"DisplayManager: Collider type not supported by scene debug draw. Add support for: " 
					+ Collider::Type_to_string(game_object->get_collider()->get_type())
				);
			}

		}
	}
}
