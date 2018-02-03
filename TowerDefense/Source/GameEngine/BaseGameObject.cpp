#include "stdafx.h"
#include "BaseGameObject.hpp"
#include "DisplayManager.hpp"
#include "Debug.hpp"
#include "Managers/GameManager.hpp"
#include "Physics.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		BaseGameObject::BaseGameObject()
		{
		}

		BaseGameObject::~BaseGameObject()
		{
			if (flag_is_started)
			{
				Managers::GameManager::on_update -= Sharp::EventHandler::Bind(&BaseGameObject::update_internal, this);
				Managers::GameManager::on_update_after_collision -= Sharp::EventHandler::Bind(
					&BaseGameObject::update_after_collision_internal,
					this
				);
			}
			Physics::removeChild(*this);
			DisplayManager::removeChild(*this);
		}

		void BaseGameObject::auto_start()
		{
			init();
			if (get_drawable())
			{
				isVisible = true; // default is true, but just in case of.
				DisplayManager::addChild(*this);
			}
			if (get_collider().get())
			{
				Physics::addChild(*this);
			}
			start();
		}

		void BaseGameObject::init()
		{
			Debug::assert_m(!flag_is_init, "BaseGameObject: already inited !");
			flag_is_init = true;
		}

		void BaseGameObject::start()
		{
			Debug::assert_m(flag_is_init, "BaseGameObject: Call init() before calling start().");
			Managers::GameManager::on_update += Sharp::EventHandler::Bind(
				&BaseGameObject::update_internal, 
				static_cast<BaseGameObject*>(this)
			);
			Managers::GameManager::on_update_after_collision += Sharp::EventHandler::Bind(
				&BaseGameObject::update_after_collision_internal, 
				static_cast<BaseGameObject*>(this)
			);
			// It is better if you addchild them yourselve
			//DisplayManager::addChild(*this);
			flag_is_started = true;
		}

		void BaseGameObject::update_internal()
		{
			if (isActive && update_active)
			{
				update();
			}
		}

		void BaseGameObject::update_after_collision_internal()
		{
			if (isActive && update_active)
			{
				update_after_collision();
			}
		}

		void BaseGameObject::update()
		{

		}

		void BaseGameObject::update_after_collision()
		{
		}

		void BaseGameObject::recycle()
		{
			//note: do not mix it with deconstructor, since this is a virutal function and desconstructor do not handle virtual function very well.
			Debug::assert_m(flag_is_started, "Recycling an element that was not started do not make sense.");
			Managers::GameManager::on_update -= Sharp::EventHandler::Bind(
				&BaseGameObject::update_internal,
				this
			);
			Managers::GameManager::on_update_after_collision -= Sharp::EventHandler::Bind(
				&BaseGameObject::update_after_collision_internal,
				this
			);
			// remove from scene in case removechildre has been forgotten
			Physics::removeChild(*this);
			DisplayManager::removeChild(*this);
			flag_is_init = false;
			flag_is_started = false;
		}
	}
}
