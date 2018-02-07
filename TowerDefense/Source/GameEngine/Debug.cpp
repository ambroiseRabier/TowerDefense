#include "stdafx.h"
#include "Debug.hpp"
#include "../../SoundsAssets.hpp"
#include "../../BaseText.hpp"

using namespace std;

namespace TowerDefense
{
	namespace GameEngine
	{

		// FPS counter working variables
		sf::Clock Debug::fpsClock;
		std::unique_ptr<sf::Text> Debug::fpsText;
		unsigned int Debug::fps = 0;
		unsigned int Debug::frame_count = 0;
		sf::Clock Debug::clock;

		void Debug::log(const string& message)
		{
			cout << get_time_as_string() << " LOG: " << message << endl;
		}

		void Debug::log(const char& message)
		{
			cout << get_time_as_string() << " LOG: " << message << endl;
		}

		void Debug::log(const float& message)
		{
			cout << get_time_as_string() << " LOG: " << message << endl;
		}

		void Debug::log(const int& message)
		{
			cout << get_time_as_string() << " LOG: " << message << endl;
		}

		void Debug::info(const std::string& message)
		{
			cout << get_time_as_string() << " INFO: " << message << endl;
		}

		void Debug::warn(const string& message)
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

		void Debug::init()
		{
			//fps text (debug only)
			fpsText = std::make_unique<sf::Text>("*FPS", *GlobalShared::default_font);
			fpsText->setCharacterSize(30);
			fpsText->setStyle(sf::Text::Bold);
			fpsText->setFillColor(sf::Color::Red);
			fpsText->setOutlineColor(sf::Color::Blue);
		}

		void Debug::update(sf::RenderTarget& window)
		{
			// fps overlay
			if(fpsClock.getElapsedTime().asSeconds() >= 1.f)
			{
				fps = frame_count;
				frame_count = 0;
				fpsClock.restart();
			}
			++frame_count;
			fpsText->setString(std::to_string(
				// prefer the long way of doing it instead of this shortcut bellow, the fps displayed is more stable.
				//static_cast<int>(std::floor(getFPS(fpsClock.restart())))
				fps
			));
			window.draw(*fpsText);
		}
		
		float Debug::getFPS(const sf::Time& time) {
			 return (1000000.0f / time.asMicroseconds());
		}

		void Debug::destroy()
		{
			fpsText.reset(nullptr);
		}
	}
}
