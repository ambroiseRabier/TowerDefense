#pragma once
#include "Screen.hpp"
#include "BaseText.hpp"
#include "GameObjects/BaseButton.hpp"

/**
 * \brief 
 * Should handle loose and win screen.
 */
class HUD: Screen
{
public:
	HUD();
	~HUD();
private:
	std::unique_ptr<BaseText> level_text;
	std::unique_ptr<BaseText> money_text;
	std::unique_ptr<TowerDefense::UI::BaseButton> pause_btn;
	std::unique_ptr<TowerDefense::UI::BaseButton> restart_btn;
	std::unique_ptr<TowerDefense::UI::BaseButton> menu_btn;
	/**
	 * \brief 
	 * Button to up speed of the game.
	 * should call GameManager to up speed by x value
	 */
	std::unique_ptr<TowerDefense::UI::BaseButton> up_speed_btn;
};

