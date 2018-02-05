#pragma once
#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

namespace TowerDefense
{
	namespace GameEngine
	{
		class SoundManager
		{
		public:
			static std::string current_music_asset_path;
			static void init();
			static void play_one_shoot(const std::string& asset_path);
			static void start_music(const std::string& asset_path);
			static void pause_music();
			static void resume_music();
			static void stop_music();
			static void set_current_music_pitch(const float& value);
			static void set_current_music_volume(const float& value);
			static void set_default_music_volume();
		};
	}
}
#endif
