#pragma once
#ifndef MINION_ASSETS_HPP
#define MINION_ASSETS_HPP
#include "Minion.hpp"

namespace TowerDefense
{
	namespace Constants
	{
		namespace MinionAssets
		{
			const std::string peon_minion = "Assets/Minion/peon_minion.png";
			const std::string tank_minion = "Assets/Minion/tank_minion.png";
			const std::string heal_minion = "Assets/Minion/heal_minion.png";
			const std::string minion_death = "Assets/Minion/minion_death.png";

			const std::unordered_map<Game::MinionId, std::string> minion_id_map {
				{Game::MinionId::Peon, peon_minion},
				{Game::MinionId::Heal, tank_minion},
				{Game::MinionId::Tank, heal_minion},
			};

			inline sf::Texture* get_minion_texture(Game::MinionId minion_id)
			{
				return GlobalShared::get_texture(minion_id_map.at(minion_id));
			}
			inline sf::Texture* get_death_texture(Game::MinionId minion_id)
			{
				return GlobalShared::get_texture(minion_death);
			}
		}
	}
}
#endif

