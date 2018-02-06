#include "stdafx.h"
#include "SoundManager.hpp"
#include "GlobalShared.hpp"
#include "SoundsAssets.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{
		std::string SoundManager::current_music_asset_path;

		void SoundManager::init()
		{
			//GlobalShared::on_window_close_game_engine_pass += Sharp::EventHandler::Bind(&SoundManager::destroy);
		}

		void SoundManager::play_one_shoot(const std::string& asset_path)
		{
			GlobalShared::get_sound(asset_path)->setLoop(false); // probably won't overlap this way :/
			GlobalShared::get_sound(asset_path)->play();
		}

		void SoundManager::start_music(const std::string& asset_path)
		{
			Debug::assert_m(
				Constants::SoundsAssets::all_assets_sounds_volume_map.at(asset_path).is_music,
				"This sound is not marked as music."
			);
			if (current_music_asset_path != "")
			{
				stop_music();
			}

			current_music_asset_path = asset_path;
			GlobalShared::get_music(asset_path)->setLoop(true); // probably won't overlap this way :/
			GlobalShared::get_music(asset_path)->setPitch(1.f);
			GlobalShared::get_music(asset_path)->setVolume(
				Constants::SoundsAssets::all_assets_sounds_volume_map.at(asset_path).volume
			);
			GlobalShared::get_music(asset_path)->setPlayingOffset(sf::Time::Zero);
			GlobalShared::get_music(asset_path)->play();
		}

		void SoundManager::pause_music()
		{
			assert(current_music_asset_path != "");
			GlobalShared::get_music(current_music_asset_path)->pause();
		}

		void SoundManager::resume_music()
		{
			assert(current_music_asset_path != "");
			assert(GlobalShared::get_music(current_music_asset_path)->getStatus() 
				== GlobalShared::get_music(current_music_asset_path)->Paused);
			GlobalShared::get_music(current_music_asset_path)->play();
		}

		void SoundManager::stop_music()
		{
			// not doing assert here because when losing then going back to menu
			// music is alreayd stopped.
			if(current_music_asset_path != ""
				&& !(GlobalShared::get_music(current_music_asset_path)->getStatus() 
				== GlobalShared::get_music(current_music_asset_path)->Playing ||
				GlobalShared::get_music(current_music_asset_path)->getStatus() 
				== GlobalShared::get_music(current_music_asset_path)->Paused))
			{
				GlobalShared::get_sound(current_music_asset_path)->stop();
				current_music_asset_path = "";
			}
		}

		void SoundManager::set_current_music_pitch(const float& value)
		{
			assert(current_music_asset_path != "");
			GlobalShared::get_music(current_music_asset_path)->setPitch(value);
		}

		void SoundManager::set_current_music_volume(const float& value)
		{
			assert(current_music_asset_path != "");
			GlobalShared::get_music(current_music_asset_path)->setVolume(value);
		}

		void SoundManager::set_default_music_volume()
		{
			assert(current_music_asset_path != "");
			GlobalShared::get_music(current_music_asset_path)->setVolume(
				Constants::SoundsAssets::all_assets_sounds_volume_map.at(current_music_asset_path).volume
			);
		}
	}
}
