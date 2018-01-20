#pragma once
#ifndef CASTLE_HPP
#define CASTLE_HPP
#include "Health.hpp"
#include "Tile.hpp"

namespace TowerDefense
{
	namespace Game
	{
		class Castle : Tile
		{
		public:
			Castle();
			~Castle();
		private:
			Health life;
			// I prefer having money here, so It can more easely become part of the gameplay (minions stealing money)
			float money;
		};
	}
}
#endif
