#include "stdafx.h"
#include "BaseGameObject.hpp"
#include "Scene.hpp"
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
			// if not already destroyed by teh call of a children of BaseGameObject then call it.
			if (!flag_is_destroyed)
			{
				destroy();
			}
		}

		void BaseGameObject::auto_start()
		{
			init();
			if (get_drawable())
			{
				isVisible = true; // default is true, but just in case of.
				Scene::addChild(*this);
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
			listenToEvents();
			// It is better if you addchild them yourselve
			//Scene::addChild(*this);
		}

		void BaseGameObject::listenToEvents()
		{
			//Managers::GameManager::on_update += Sharp::EventHandler::Bind(&BaseGameObject::update, static_cast<BaseGameObject*>(this));
		}

		void BaseGameObject::unListenToEvents()
		{
			//Managers::GameManager::on_update -= Sharp::EventHandler::Bind(&BaseGameObject::update, this);
		}

		void BaseGameObject::update()
		{
			//Debug::log("BaseGameObject:: update");
		}

		void BaseGameObject::recycle()
		{
			// remove from scene in case removechildre has been forgotten
			Physics::removeChild(*this);
			Scene::removeChild(*this);
			unListenToEvents();
			flag_is_init = false;
		}

		void BaseGameObject::destroy()
		{
			Debug::log("BaseGameObject::destroy()");
			if (!flag_is_destroyed)
			{
				flag_is_destroyed = true;
				unListenToEvents();
				Physics::removeChild(*this);
				Scene::removeChild(*this);
			}
		}
	}
}
