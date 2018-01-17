#include "Debug.hpp"
#include "stdafx.h"

namespace TowerDefense
{
	namespace GameEngine
	{
		void Debug::log(const std::string& message)
		{
			std::cout << "LOG: " << message << std::endl;
		}

		void Debug::warning(const std::string& message)
		{
			std::cout << "WARNING: " << message << std::endl;
		}

		void Debug::assert_m(bool assertion, const std::string& message)
		{
			if (!assertion)
			{
				std::cout << "ASSERTION FAILED: " << message << std::endl;
				// yeah I know, the expression is false when it comes here, but don't want to decompose assert method !
				assert(assertion);
			}
		}
	}
}
