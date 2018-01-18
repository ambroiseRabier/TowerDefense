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
			Debug::assert_m(
				flag_is_destroyed, 
				"BaseGameObject: Did you forgot to call destroy() before deleting me? Or maybe you forgot to add base call to overriden destroy function."
			);
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
			Managers::GameManager::on_update += Sharp::EventHandler::Bind(&BaseGameObject::update, this);
		}

		void BaseGameObject::unListenToEvents()
		{
			Managers::GameManager::on_update -= Sharp::EventHandler::Bind(&BaseGameObject::update, this);
		}

		void BaseGameObject::update()
		{
		}

		void BaseGameObject::recycle()
		{
			// remove from scene in case removechildre has been forgotten
			Physics::removeChild(*this);
			Scene::removeChild(*this);
			unListenToEvents();
			init();
		}

		void BaseGameObject::destroy()
		{
			// actually, it would be better to set this flag to true at the end of
			// last overrided destroy, but it's ok it will still work without flaw
			// since program is run synchronousely.
			flag_is_destroyed = true;
			unListenToEvents();
			Physics::removeChild(*this);
			Scene::removeChild(*this);
		}
	}
}