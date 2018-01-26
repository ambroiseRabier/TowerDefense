#include "stdafx.h"
#include "Mathf.hpp"

using namespace sf;
using namespace std;
namespace TowerDefense
{
	namespace Utils
	{
		float magnitude(const Vector2f& vec)
		{
			return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
		}

		Vector2f normalize(const Vector2f& vec)
		{
			return vec / magnitude(vec);
		}

		bool rand_bool()
		{
			return (std::rand() % 2) == 0 ? true : false;
		}
		//cannot find :/ ? wtf not public or so ?
		// multiply with
		//constexpr double degToRad() { return M_PI / 180; }
		// multiply with
		//constexpr double radToDeg() { return 180 / M_PI; }
	}
}
