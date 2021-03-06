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
			const std::string heal_minion = "Assets/Minion/heal_minion.png";
			const std::string tank_minion = "Assets/Minion/tank_minion.png";
			const std::string minion_death = "Assets/Minion/minion_death.png";

			const std::unordered_map<Game::MinionId, std::string> minion_id_map {
				{Game::MinionId::Peon, peon_minion},
				{Game::MinionId::Heal, heal_minion},
				{Game::MinionId::Tank, tank_minion},
			};

			inline sf::Texture* get_minion_texture(Game::MinionId minion_id)
			{
				return GlobalShared::get_texture(minion_id_map.at(minion_id));
			}

			inline sf::Texture* get_death_texture(Game::MinionId minion_id)
			{
				return GlobalShared::get_texture(minion_death);
			}
			
			const std::string minion_peon_hit = "Assets/SFX/Minions/minion_peon_hit.wav";
			//const std::string minion_heal_hit = "Assets/SFX/Minions/minion_heal_hit.wav";
			const std::string minion_tank_hit = "Assets/SFX/Minions/minion_tank_hit.wav";
			const std::string minion_peon_death = "Assets/SFX/Minions/minion_peon_death.wav";
			const std::string minion_heal_death = "Assets/SFX/Minions/minion_heal_death.wav";
			const std::string minion_tank_death = "Assets/SFX/Minions/minion_tank_death.wav";

			const std::unordered_map<Game::MinionId, std::string> minion_hit_sound_map {
				{Game::MinionId::Peon, minion_peon_hit},
				//{Game::MinionId::Heal, minion_heal_hit},
				{Game::MinionId::Tank, minion_tank_hit},
			};

			const std::unordered_map<Game::MinionId, std::string> minion_death_sound_map {
				{Game::MinionId::Peon, minion_peon_death},
				{Game::MinionId::Heal, minion_heal_death},
				{Game::MinionId::Tank, minion_tank_death},
			};
			
			inline std::string get_minion_hit_sound(Game::MinionId minion_id)
			{
				return minion_hit_sound_map.at(minion_id);
			}

			inline std::string get_death_death_sound(Game::MinionId minion_id)
			{
				return minion_death_sound_map.at(minion_id);
			}
		}
	}
}
#endif

