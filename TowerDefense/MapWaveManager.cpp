#include "stdafx.h"
#include "MapWaveManager.hpp"
#include "Health.hpp"
#include "Minion.hpp"
#include "GlobalShared.hpp"
#include "MapManager.hpp"

using namespace TowerDefense::Game;
namespace TowerDefense
{
	namespace Managers
	{
		std::list<GameEngine::BaseGameObject*> MapWaveManager::instanciated_elements;

		void MapWaveManager::init()
		{
			// no need to unlisten the event, since MapManager.on_destroy_level gonna be destroyed anyway.
			MapManager::on_destroy_level += Sharp::EventHandler::Bind(&MapWaveManager::destroy_current_level);
		}

		void MapWaveManager::start_wave_spawn()
		{
			auto minion = Minion::create_peon(MapManager::get_spawn().map_pos);
			minion->get_transformable().setPosition(
				MapManager::get_spawn().get_transformable().getPosition()
			);
			minion->auto_start();
			instanciated_elements.push_back(minion);
		}

		void MapWaveManager::destroy_me(GameEngine::BaseGameObject& to_delete)
		{
			// this obviously do not work, because the pointer is different.
			// we have to search by value.
			//instanciated_elements.remove(&base_game_object);
			for (auto base_game_object : instanciated_elements)
			{
				if (to_delete == *base_game_object)
				{
					instanciated_elements.remove(base_game_object);
					delete base_game_object;
					base_game_object = nullptr;
					break;
				}
			}
		}

		void MapWaveManager::destroy_current_level()
		{
			if (!instanciated_elements.empty())
			{
				for (std::list<GameEngine::BaseGameObject*>::value_type base_game_object : instanciated_elements)
				{
					delete base_game_object;
					base_game_object = nullptr;
				}
				instanciated_elements.clear();
			}
		}
	}
}
