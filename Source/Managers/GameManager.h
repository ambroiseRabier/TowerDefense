#pragma once
#include "Utils/Singleton.h"
#include "Header.h"

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
