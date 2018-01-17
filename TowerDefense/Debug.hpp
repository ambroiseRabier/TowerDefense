#pragma once
#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <string>

namespace TowerDefense
{
	namespace GameEngine
	{
		class Debug
		{
		public:
			/**
			 * \brief Simple log function with date.
			 */
			static void log(const std::string& message);
			/**
			 * \brief Simple warning function with date.
			 */
			static void warning(const std::string& message);
			/**
			 * \brief Wrap assert function with date and message.
			 * \param assertion 
			 * \param message 
			 */
			static void assert_m(bool assertion, const std::string& message);
		};
	}
}
#endif

