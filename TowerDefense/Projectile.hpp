#pragma once
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "GameEngine/BaseGameObject.hpp"

namespace TowerDefense
{
	namespace Game
	{
		class Projectile : public TowerDefense::GameEngine::BaseGameObject
		{
		public:
			Projectile();
			~Projectile();
		};
	}
}
#endif
