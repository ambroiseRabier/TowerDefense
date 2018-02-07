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

		Vector2f to_dir(const float& angle_degree)
		{
			return Vector2f(
				std::cos(angle_degree / 180.f * M_PI),
				std::sin(angle_degree / 180.f * M_PI)
			);
		}

		float look_at_angle(const Vector2f& me, const Vector2f& look_at)
		{
			return static_cast<float>(std::atan2f(
				look_at.y - me.y, 
				look_at.x - me.x
			) / M_PI * 180.f);
		}

		Vector2f look_at_dir(const Vector2f& me, const Vector2f& look_at)
		{
			return normalize(look_at - me);
		}

		
		/**
		 * http://www.migapro.com/circle-and-rotated-rectangle-collision-detection/
		 * Pythagorean theorem
		 * @param fromX
		 * @param fromY
		 * @param toX
		 * @param toY
		 */
		double findDistance(double fromX, double fromY, double toX, double toY){
			const double a = abs(fromX - toX);
			const double b = abs(fromY - toY);
			return sqrt((a * a) + (b * b));
		}

		//cannot find :/ ? wtf not public or so ?
		// multiply with
		//constexpr double degToRad() { return M_PI / 180; }
		// multiply with
		//constexpr double radToDeg() { return 180 / M_PI; }
	}
}
