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
		class BaseText : public GameEngine::BaseGameObject
		{
		public:
			BaseText(const std::string& text = "");
			void set_text(const std::string& new_text) const;
			const sf::Text& get_text() const;

		private:
			sf::Text* text;
		};
	}
}
#endif
