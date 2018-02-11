#pragma once
namespace TowerDefense
{
	namespace ExternalConstants
	{
		struct Config
		{
			unsigned int fps_limit;
		};

		inline void from_json(const json& j, Config& p) {
			p.fps_limit = j.at("fps_limit").get<unsigned int>();
		}
	}
}
