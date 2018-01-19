#pragma once
#ifndef DEBUG_HPP
#define DEBUG_HPP

namespace TowerDefense
{
	namespace GameEngine
	{
		// todo: add index of log and date and class from wich it originated? probably done somewhere in the world.
		class Debug
		{
		public:
			/**
			 * \brief Simple log function with date. (for debug purpose)
			 */
			static void log(const std::string& message);
			static void log(const char& message);
			static void log(const float& message);
			static void log(const int& message);
			/**
			 * \brief Simple log function with date.
			 */
			static void info(const std::string& message);
			/**
			 * \brief Simple warn function with date.
			 */
			static void warn(const std::string& message);
			/**
			 * \brief Wrap assert function with date and message.
			 * \param assertion 
			 * \param message 
			 */
			static void assert_m(bool assertion, const std::string& message);
			static std::string get_time_as_string();
			static void start_clock();
		private:
			static sf::Clock clock;
		};
	}
}
#endif

