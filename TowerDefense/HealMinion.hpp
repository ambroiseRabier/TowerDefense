#pragma once
#ifndef HEAL_MINION_HPP
#define HEAL_MINION_HPP
#include "Minion.hpp"

namespace TowerDefense
{
	namespace Game
	{
		class HealMinion : public Minion
		{
		public:
			HealMinion();
			// I keep the minion_id parameter in case we have many healminion. (like peonHealMinion, bossHealMinion maybe)
			HealMinion(sf::Vector2u map_pos, const MinionId minion_id);
			~HealMinion();
			void on_game_object_overlap(GameObject& game_object) override;
		protected:
			std::vector<Minion*> minion_vector;
			void start() override;
			unsigned int heal_time_out_id = 0;
			void heal_minions();
			void start_heal_time_out();
		};
	}
}
#endif
