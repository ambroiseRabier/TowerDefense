#pragma once
#ifndef SOUNDS_ASSETS_HPP
#define SOUNDS_ASSETS_HPP
#include "TowerAssets.hpp"
#include "MinionAssets.hpp"

namespace TowerDefense
{
	namespace Constants
	{
		/**
		 * \brief Path of the assets (images, sounds, ...)
		 */
		namespace SoundsAssets
		{
			struct SoundParams
			{
				SoundParams(const float volume, const bool is_music)
					: volume(volume),
					  is_music(is_music)
				{
				}

				const float volume;
				const bool is_music;
				// max instance of it todo
			};

			const std::string missing_sound = "Assets/SFX/missing_sound.mp3";
			const std::string game_loop = "Assets/Music/Game_BGM.wav";
			const std::string btn_click_ui = "Assets/SFX/UI/btn_click_ui.wav";
			const std::unordered_map<std::string, SoundParams> all_assets_sounds_volume_map {
				{missing_sound, {40.f, false}},
				{game_loop, {35.f, true}},
				{btn_click_ui, {60.f, false}},
				{TowerAssets::shoot_stone_tower, {40.f, false}},
				{TowerAssets::shoot_freeze_tower, {40.f, false}},
				{TowerAssets::shoot_explosiv_tower, {40.f, false}},
				{TowerAssets::build_stone_tower, {60.f, false}},
				{TowerAssets::build_freeze_tower, {60.f, false}},
				{TowerAssets::build_explosiv_tower, {60.f, false}},
				{MinionAssets::minion_peon_hit, {60.f, false}},
				{MinionAssets::minion_heal_death, {60.f, false}},

			};
			const float pause_music_volume = 10.f;

			/**
			 * \brief Should be exactly similar to game_speed_choices constant in GameDesign.hpp .
			 */
			const float game_speed_pitch_choices[4] = {1.0f, 1.05f, 1.1f, 0.9f};

		}
	}
}
#endif
