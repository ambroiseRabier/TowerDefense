#include "stdafx.h"
#include "BaseText.hpp"
#include "Config.hpp"
#include "GlobalShared.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense
{
	namespace UI
	{
		BaseText::BaseText(const std::string& new_text)
		{
			// the compiler doesn't understand optyionnal argument on int size,
			// that's why I had to make two constrctor, weird :/
			constructor_internal(new_text, 36);
		}

		BaseText::BaseText(const std::string& new_text, const unsigned int size)
		{
			constructor_internal(new_text,size);
		}

		void BaseText::constructor_internal(const std::string& new_text, const unsigned int size)
		{
			std::shared_ptr<sf::Text> my_text = std::make_shared<sf::Text>();
			text = my_text.get();
			set_drawable(std::move(my_text));
			z_index = Constants::ZIndex::ui;
			set_text(new_text);
			text->setOutlineColor(sf::Color::White);
			// setOutlineThickness has memory leaks (I've confirmed it)
			// https://github.com/SFML/SFML/issues/1233
			//text->setOutlineThickness(1.f);
			text->setFont(*GlobalShared::default_font);
			text->setCharacterSize(size);
		}

		void BaseText::set_text(const std::string& new_text)
		{
			text->setString(new_text);
		}

		void BaseText::set_text_color(const sf::Color color)
		{
			text->setFillColor(color);
		}

		const sf::Text& BaseText::get_text() const
		{
			Debug::assert_m(text, "BaseText: text being nullptr is unexpected.");
			return *text;
		}
	}
}
