#pragma once
#ifndef PHANTOM_HPP
#define PHANTOM_HPP
#include "GameEngine/BaseGameObject.hpp"
#include "Utils/Event.h"


namespace TowerDefense
{
	namespace Game
	{
		// forward declaration.
		enum class TowerId;
		class Phantom : public GameEngine::BaseGameObject
		{
		public:
			Phantom();
			void set_tower_id(TowerId new_tower_id);
			Sharp::Event<void> on_click_valid;
			Sharp::Event<void> on_click_cancel;
			sf::Vector2u valid_map_pos; // todo: read only
			sf::Sprite* sprite;
			void update() override;
			void on_mouse_click_front(bool left) override;
			void update_position();
			TowerId tower_id;
		};
	}
}
#endif
