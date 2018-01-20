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
	// I prefer having money here, so It can more easely become part of the gameplay (minions stealing money)
	float money;
};

