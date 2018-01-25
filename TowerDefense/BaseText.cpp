#include "stdafx.h"
#include "BaseText.hpp"
#include "CastUtils.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense
{
	namespace UI
	{
		BaseText::BaseText(const std::string& new_text)
		{
			std::unique_ptr<sf::Text> my_text = std::make_unique<sf::Text>();
			text = my_text.get();
			set_drawable(
				std::move(static_cast_ptr<sf::Drawable>(
					my_text
				))
			);
			z_index = Constants::ZIndex::ui_start;
			set_text(new_text);
			text->setOutlineColor(sf::Color::White);
			text->setOutlineThickness(1.f);
			text->setFont(*GlobalShared::default_font);
			text->setCharacterSize(36);
		}

		void BaseText::set_text(const std::string& new_text) const
		{
			text->setString(new_text);
		}

		const sf::Text& BaseText::get_text() const
		{
			Debug::assert_m(text, "BaseText: text being nullptr is unexpected.");
			return *text;
		}
	}
}
