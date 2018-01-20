#include "stdafx.h"
#include "BaseText.hpp"


BaseText::BaseText()
{
}


BaseText::~BaseText()
{
}

void BaseText::set_text(const std::string& new_text)
{
	text->setString(new_text);
}
