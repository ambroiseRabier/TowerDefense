#pragma once
#ifndef MATHF_HPP
#define MATHF_HPP

namespace TowerDefense
{
	namespace Utils
	{
		float magnitude(const sf::Vector2f& vec);
		sf::Vector2f normalize(const sf::Vector2f& vec);
		bool rand_bool();
	}
}
#endif
