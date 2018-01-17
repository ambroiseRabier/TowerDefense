#include "Debug.hpp"
#include "stdafx.h"

using namespace std;

namespace TowerDefense
{
	namespace GameEngine
	{
		sf::Clock Debug::clock;

		void Debug::log(const string& message)
		{
			cout << get_time_as_string() << " LOG: " << message << endl;
		}

		void Debug::info(const std::string& message)
		{
			cout << get_time_as_string() << " INFO: " << message << endl;
		}

		void Debug::warning(const string& message)
		{
			cout << get_time_as_string() << " WARNING: " << message << endl;
		}

		void Debug::assert_m(bool assertion, const string& message)
		{
			if (!assertion)
			{
				cout << get_time_as_string() << " ASSERTION FAILED: " << message << endl;
				// yeah I know, the expression is false when it comes here, but don't want to decompose assert method !
				assert(assertion);
			}
		}

		string Debug::get_time_as_string()
		{
			const unsigned int time_since_start = clock.getElapsedTime().asMilliseconds();
			const unsigned int millis = time_since_start % 1000;
			const unsigned int seconds = (time_since_start/1000) % 60;
			const unsigned int minutes = (time_since_start/(1000*60)) % 60;
			const unsigned int hours = (time_since_start/(1000*60*60)) % 24;
			string HH = to_string(hours);
			string MM = to_string(minutes);
			string SS = to_string(seconds);
			string ms = to_string(millis);
			// applying pad_end()
			HH.insert(HH.begin(), 2 - HH.length(), '0');
			MM.insert(MM.begin(), 2 - MM.length(), '0');
			SS.insert(SS.begin(), 2 - SS.length(), '0');
			ms.insert(ms.begin(), 4 - ms.length(), '0');
			return HH + ":" + HH + ":" + SS + ":" + ms;
		}
	}
}
