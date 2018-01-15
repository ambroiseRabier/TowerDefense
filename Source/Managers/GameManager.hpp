#pragma once
// to know : https://stackoverflow.com/questions/152555/h-or-hpp-for-your-class-definitions
#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include "stdafx.h"
#include "Utils/Singleton.hpp"

using namespace std;

namespace TowerDefense
{
	namespace Managers
	{
		class GameManager
			{
			public:
			   GameManager() {};
			   ~GameManager() {};
			   bool openLogFile(string);
			   void writeToLogFile(string);
			   bool closeLogFile(string);
			private:
			};
		
		typedef Singleton<GameManager> LoggerSingleton;   // Global declaration
	}
}
#endif
