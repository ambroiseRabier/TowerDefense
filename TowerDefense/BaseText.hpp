#pragma once
#include "GameEngine/BaseGameObject.hpp"

/**
 * \brief 
 * Class to display text (for hud mostly)
 */
class BaseText:public TowerDefense::GameEngine::BaseGameObject
{
public:
	BaseText();
	~BaseText();
	void set_text(const std::string& new_text);
private:
	std::shared_ptr<sf::Text> text; // don't forget to reset it on destroy.

};

