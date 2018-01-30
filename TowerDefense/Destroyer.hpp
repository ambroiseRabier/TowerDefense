#pragma once
#ifndef DESTROYER_HPP
#define DESTROYER_HPP
#include "GameEngine/BaseGameObject.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		/**
		 * \brief Utility class to destroy element just before rendering.
		 * Be ause you cannot destroy in an event callback, in update or in collision callback (sadly)
		 */
		class Destroyer
		{
		public:
			static void destroy_end_of_frame(BaseGameObject* pointer);
			static void init();
			static void update();
		private:
			static std::vector<BaseGameObject*> destroy_vector;
		};
	}
}
#endif
