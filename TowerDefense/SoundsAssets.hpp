#pragma once
#ifndef SOUNDS_ASSETS_HPP
#define SOUNDS_ASSETS_HPP

namespace TowerDefense
{
	namespace Constants
	{
		/**
		 * \brief Path of the assets (images, sounds, ...)
		 */
		namespace SoundsAssets
		{
			const std::string missing_sound = "Assets/SFX/missing_sound.mp3";
			const std::string btn_click = "Assets/SFX/death1.wav";
			const std::string game_loop = "Assets/Music/Game_BGM.wav";
			const std::unordered_map<std::string, float> all_assets_sounds_volume_map {
				{missing_sound, 40.f},
				{btn_click, 60.f},
				{game_loop, 60.f},
			};
			const float pause_music_volume = 20.f;

			/**
			 * \brief Should be exactly similar to game_speed_choices constant in GameDesign.hpp .
			 */
			const float game_speed_pitch_choices[4] = {1.0f, 1.05f, 1.1f, 0.9f};
		}
	}
}
#endif
