#pragma once
#include <SFML/Graphics/Transformable.hpp>

namespace TowerDefense
{
	namespace Utils
	{
		/// orignal name that I never took from another engine.
		class MonoBehaviour
		{
		public:
			MonoBehaviour();
			~MonoBehaviour();
			sf::Transformable get_transform;
		protected:
			sf::Transformable transform;
		};
	}
}
