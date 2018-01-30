#include "stdafx.h"
#include "Destroyer.hpp"
#include "GlobalShared.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		std::vector<BaseGameObject*> Destroyer::destroy_vector;

		void Destroyer::destroy_end_of_frame(BaseGameObject* pointer)
		{
			destroy_vector.push_back(pointer);
		}

		void Destroyer::init()
		{
			GlobalShared::on_window_close += Sharp::EventHandler::Bind(&Destroyer::update);
		}

		void Destroyer::update()
		{
			if (destroy_vector.empty())
				return;
			// si deux destroyed ?

			for (auto pointer : destroy_vector)
			{
				delete pointer;
				pointer = nullptr;
			}
			destroy_vector.clear();
		}
	}
}
