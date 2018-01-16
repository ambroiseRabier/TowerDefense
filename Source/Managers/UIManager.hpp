#pragma once
// to know : https://stackoverflow.com/questions/152555/h-or-hpp-for-your-class-definitions
#ifndef UI_MANAGER_HPP
#define UI_MANAGER_HPP

namespace TowerDefense
{
	namespace Managers
	{
		class UIManager
		{
		public:
			UIManager() {}
			~UIManager() {};
			static void OpenPause();
			static void Init();
			static void Update();
		private:
		};
	}
}
#endif
