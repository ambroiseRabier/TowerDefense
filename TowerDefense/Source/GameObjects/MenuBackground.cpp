#include "stdafx.h"
#include "MenuBackground.hpp"
#include "GameEngine/Debug.hpp"
#include "../../GlobalShared.hpp"
#include "../../Config.hpp"
#include "../../UIAssets.hpp"

using namespace TowerDefense::GameEngine;
namespace TowerDefense
{
	namespace UI
	{
		void MenuBackground::init()
		{
			BaseGameObject::init();
			set_drawable(
				std::make_shared<sf::Sprite>(*GlobalShared::get_texture(Constants::UIAssets::menu_background))
			);
			// since I used std::move, do not call my_sprite anymore !

			z_index = Constants::ZIndex::ui_background;
			collider = std::make_shared<Collider>( // todo: unique would be better no ?
				sf::FloatRect(0,0,200,200),
				Collider::Tag::UI
			);
			transformable->setPosition(200,200);
		}

		void MenuBackground::on_mouse_overlap()
		{
		}

		void MenuBackground::on_mouse_overlap_front()
		{
		}

		void MenuBackground::on_mouse_click(bool left)
		{
			Debug::log("on_mouse_click background " + left);

		}

		void MenuBackground::on_mouse_click_front(bool left)
		{
			Debug::log("on_mouse_click_front background " + left);
		}
	}
}
