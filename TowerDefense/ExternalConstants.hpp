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
		};

		inline void from_json(const json& j, Config& p) {
			// if one exception occur, multiple settings might use default.
			// solution would be use a try catch for every field.
			try
			{
				p.fps_limit = j.at("fps_limit").get<unsigned int>();
				p.window_width = j.at("window_width").get<unsigned int>();
				p.window_height = j.at("window_height").get<unsigned int>();
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}
	}
}
