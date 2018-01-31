#pragma once
#ifndef CASTLE_HPP
#define CASTLE_HPP
#include "Health.hpp"
#include "Tile.hpp"

namespace TowerDefense
{
	namespace Game
	{
		class Castle : public Tile
		{
		public:
			Castle(const sf::Vector2u map_pos);
			~Castle();
			Health& get_health() const;
		protected:
			void update_position() override;
		private:
			std::unique_ptr<Health> health;
		};
	}
}
#endif
