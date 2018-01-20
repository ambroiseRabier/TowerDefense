#pragma once
#include "GameEngine/BaseGameObject.hpp"
#include "Health.hpp"

class Castle : TowerDefense::GameEngine::BaseGameObject
{
public:
	Castle();
	~Castle();
private:
	Health life;
};

