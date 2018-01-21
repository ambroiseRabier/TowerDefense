#pragma once
#ifndef BASE_TEXT_HPP
#define BASE_TEXT_HPP
#include "GameEngine/BaseGameObject.hpp"

namespace TowerDefense
{
	namespace UI
	{
		/**
		 * \brief 
		 * Class to display text (for hud mostly)
		 */
		class BaseText : public TowerDefense::GameEngine::BaseGameObject
		{
		public:
			BaseText(const std::string& text);
			~BaseText();
			void set_text(const std::string& new_text);
		private:
			std::shared_ptr<sf::Text> text; // don't forget to reset it on destroy.
		};
	}
}
#endif
