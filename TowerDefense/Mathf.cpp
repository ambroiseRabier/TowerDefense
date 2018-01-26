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
	}
}
