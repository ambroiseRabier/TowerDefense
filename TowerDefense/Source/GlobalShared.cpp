#include "stdafx.h"
#include "../GlobalShared.hpp"
#include "Utils/Event.h"
#include "../Assets.hpp"
#include "../SoundsAssets.hpp"
#include "GameEngine/Debug.hpp"

namespace TowerDefense
{
	/**
	 * \brief Things that are loaded before the start of the game and that I don't intend to destroy.
	 */
	namespace GlobalShared
	{
		sf::Font* default_font;
		std::unordered_map<std::string, std::unique_ptr<sf::Texture>> stringToTexture;
		std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> stringToSoundBuffer;
		std::unordered_map<std::string, std::unique_ptr<sf::Sound>> stringToSound;
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> stringToMusic;

		Sharp::Event<void> on_window_close;
		Sharp::Event<void> on_window_close_game_engine_pass;
;
		void load_all_textures()
		{
			if (Constants::Assets::all_assets_textures.empty())
				return;

			// todo: should send a warning if duplicated string
			for (const auto string : Constants::Assets::all_assets_textures)
			{
				std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
				texture->loadFromFile(string);
				stringToTexture[string] = std::move(texture);
			}
		}


		void load_all_sounds()
		{
			if (Constants::SoundsAssets::all_assets_sounds_volume_map.empty())
				return;

			// todo: should send a warning if duplicated string
			for (const auto pair : Constants::SoundsAssets::all_assets_sounds_volume_map)
			{
				if (pair.second.is_music)
				{
					std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
					music->openFromFile(pair.first);
					stringToMusic[pair.first] = std::move(music);
				}
				else
				{
					std::unique_ptr<sf::SoundBuffer> sound_buffer = std::make_unique<sf::SoundBuffer>();
					std::unique_ptr<sf::Sound > sound = std::make_unique<sf::Sound>();
					sound_buffer->loadFromFile(pair.first);
					// set sound after loading sound_buffer.
					sound->setBuffer(*sound_buffer);
					sound->setVolume(pair.second.volume); // we could add more initial params if needed.
					stringToSoundBuffer[pair.first] = std::move(sound_buffer);
					stringToSound[pair.first] = std::move(sound);
				}
			}
		}


		sf::Texture* get_texture(const std::string& asset_path)
		{
			if (!stringToTexture[asset_path])
			{
				GameEngine::Debug::warn(
					"GlobalShared: Texture has no been loaded for asset : " + asset_path
				);
				return stringToTexture[Constants::Assets::missing_texture_tile].get();
			}
			return stringToTexture[asset_path].get();
		}

		sf::SoundBuffer* get_sound_buffer(const std::string& asset_path)
		{
			if (!stringToTexture[asset_path])
			{
				GameEngine::Debug::warn(
					"GlobalShared: SoundsBuffer has no been loaded for asset : " + asset_path
				);
				return stringToSoundBuffer[Constants::SoundsAssets::missing_sound].get();
			}
			return stringToSoundBuffer[asset_path].get();
		}

		sf::Sound* get_sound(const std::string& asset_path)
		{
			if (!stringToSound[asset_path])
			{
				GameEngine::Debug::warn(
					"GlobalShared: Sounds has no been loaded for asset : " + asset_path
				);
				return stringToSound[Constants::SoundsAssets::missing_sound].get();
			}
			return stringToSound[asset_path].get();
		}

		sf::Music* get_music(const std::string& asset_path)
		{
			if (!stringToMusic[asset_path])
			{
				GameEngine::Debug::warn(
					"GlobalShared: Sounds has no been loaded for asset : " + asset_path
				);
				return nullptr;
			}
			return stringToMusic[asset_path].get();
		}

		void destroy()
		{
			delete default_font; default_font = nullptr;

			if (!stringToTexture.empty())
			{
				for (auto&& pair : stringToTexture)
				{
					pair.second.reset(nullptr);
				}
				stringToTexture.clear();
			}

			// before buffer.
			if (!stringToSound.empty())
			{
				for (auto&& pair : stringToSound)
				{
					pair.second.reset(nullptr);
				}
				stringToSound.clear();
			}

			if (!stringToMusic.empty())
			{
				for (auto&& pair : stringToMusic)
				{
					pair.second.reset(nullptr);
				}
				stringToMusic.clear();
			}

			if (!stringToSoundBuffer.empty())
			{
				for (auto&& pair : stringToSoundBuffer)
				{
					pair.second.reset(nullptr);
				}
				stringToSoundBuffer.clear();
			}
			
		}
	}
}
