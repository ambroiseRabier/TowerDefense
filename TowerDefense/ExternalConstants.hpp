#pragma once
namespace TowerDefense
{
	namespace ExternalConstants
	{
		struct Config
		{
			unsigned int fps_limit = 144;
			unsigned int window_width = 1280;
			unsigned int window_height = 720;
			bool debug_draw_collider = false;
		};

		inline void from_json(const json& j, Config& p) {
			// if one exception occur, multiple settings might use default.
			// solution would be use a try catch for every field.
			try
			{
				p.fps_limit = j.at("fps_limit").get<unsigned int>();
				p.window_width = j.at("window_width").get<unsigned int>();
				p.window_height = j.at("window_height").get<unsigned int>();
				p.debug_draw_collider = j.at("debug_draw_collider").get<bool>();
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}

		struct GameDesign
		{
			std::array<float,4> game_speed_choices = {1.0f, 2.0f, 3.0f, 0.5f};
		};

		inline void from_json(const json& j, GameDesign& p) {
			// if one exception occur, multiple settings might use default.
			// solution would be use a try catch for every field.
			try
			{
				p.game_speed_choices = j.at("game_speed_choices").get<std::array<float,4>>();
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}
	}
}
