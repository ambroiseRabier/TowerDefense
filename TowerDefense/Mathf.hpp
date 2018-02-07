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
		sf::Vector2f to_dir(const float& angle_degree);
		float look_at_angle(const sf::Vector2f& me, const sf::Vector2f& look_at);
		sf::Vector2f look_at_dir(const sf::Vector2f& me, const sf::Vector2f& look_at);
		double findDistance(double fromX, double fromY, double toX, double toY);
	}
}
#endif
