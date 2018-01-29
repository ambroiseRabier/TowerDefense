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
			if (flag_is_started)
			{
				Managers::GameManager::on_update -= Sharp::EventHandler::Bind(&BaseGameObject::update, this);
			}
			Physics::removeChild(*this);
			Scene::removeChild(*this);
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
			Managers::GameManager::on_update += Sharp::EventHandler::Bind(&BaseGameObject::update, static_cast<BaseGameObject*>(this));
			// It is better if you addchild them yourselve
			//Scene::addChild(*this);
			flag_is_started = true;
		}

		void BaseGameObject::update()
		{

		}

		void BaseGameObject::recycle()
		{
			Debug::assert_m(flag_is_started, "Recycling an element that was not started do not make sense.");
			Managers::GameManager::on_update -= Sharp::EventHandler::Bind(&BaseGameObject::update, this);
			// remove from scene in case removechildre has been forgotten
			Physics::removeChild(*this);
			Scene::removeChild(*this);
			flag_is_init = false;
			flag_is_started = false;
		}
	}
}
