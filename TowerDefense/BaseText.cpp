#include "stdafx.h"
#include "BaseText.hpp"

namespace TowerDefense
{
	namespace UI
	{
		BaseText::BaseText(const std::string& text)
		{
		}


		BaseText::~BaseText()
		{
		}

		void BaseText::set_text(const std::string& new_text)
		{
			text->setString(new_text);
		}
	}
}
