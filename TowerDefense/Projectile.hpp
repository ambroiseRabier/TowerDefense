#pragma once
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "GameEngine/BaseGameObject.hpp"


class Projectile: public TowerDefense::GameEngine::BaseGameObject
{
public:
	Projectile();
	~Projectile();

};
#endif

