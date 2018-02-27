#include "stdafx.h"
#include "../GlobalShared.hpp"
#include "Utils/Event.h"
#include "../Assets.hpp"
#include "../SoundsAssets.hpp"
#include "GameEngine/Debug.hpp"
#include "../Others.hpp"

namespace TowerDefense
{
	/**
	 * \brief Things that are loaded before the start of the game and that I don't intend to destroy.
	 */
	namespace GlobalShared
	{
		ExternalConstants::Config config;
		ExternalConstants::GameDesign game_design;
		ExternalConstants::LevelDesign level_design;
		sf::Font* default_font;
		std::unordered_map<std::string, std::unique_ptr<sf::Texture>> stringToTexture;
		std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> stringToSoundBuffer;
		std::unordered_map<std::string, std::unique_ptr<sf::Sound>> stringToSound;
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> stringToMusic;

		Sharp::Event<void> on_window_close;
		Sharp::Event<void> on_window_close_game_engine_pass;
;


		void load_all_fonts()
		{
			// allocate on heap since this will stay longer then the stack of this function
			// then copy pointer on GlobalShared
			sf::Font* font = DBG_NEW sf::Font();
			font->loadFromFile(Constants::Assets::default_font);
			default_font = font;
		}

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
					music->setVolume(pair.second.volume);
					stringToMusic[pair.first] = std::move(music);
				}
				else
				{
					std::unique_ptr<sf::SoundBuffer> sound_buffer = std::make_unique<sf::SoundBuffer>();
					std::unique_ptr<sf::Sound > sound = std::make_unique<sf::Sound>();
					const bool file_found = sound_buffer->loadFromFile(pair.first);
					if (!file_found) {
						Debug::warn("File not found: " + pair.first);
						continue;
					}
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
					"GlobalShared: Music has no been loaded for asset : " + asset_path
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

		void load_all_settings()
		{
			// the other option is with is_discarded with allow_exceptions to false on parse()
			// https://github.com/nlohmann/json/issues/458 
			validate_json(Constants::Config::config_file);
			ExternalConstants::from_json(
				json::parse(std::ifstream(Constants::Config::config_file)),
				config
			);
			validate_json(Constants::Config::game_design_file);
			ExternalConstants::from_json(
				json::parse(std::ifstream(Constants::Config::game_design_file)),
				game_design
			);
			validate_json(Constants::Config::level_design_file);
			ExternalConstants::from_json(
				json::parse(std::ifstream(Constants::Config::level_design_file)),
				level_design
			);
			//config = config_j; operator = ambiguous :/, don't know why
		}

		void validate_json(const std::string& path)
		{
			// since the stream become buggy after json::accept, i've created another stream here.
			std::ifstream in (path);
			// returning int c= 5; after throw only to avoid confusing 
			// line number in debugger --' (it throw END of the next line otherwise)
			// OK STREAM IS MAGIC THING, it should work, but it don't. so no warning omg.
			// huum maybe just again this bad line exception --'
			// !is_open() or !in or fail()
			if (!fileExists(path))
			{
				Debug::warn(path + " was not found.");
				throw path + " was not found.";
				int c= 5;
			}
			if (in.peek() == std::ifstream::traits_type::eof())
			{
				Debug::warn(path + " is an empty json.");
				throw path + " is an empty json.";
				int c= 5;
			}
			// using json::accept(in) invalidate the stream after (parse will throw an exception don't know why :/)
			if (!json::accept(in))
			{
				Debug::warn(path + " is not a valid json.");
				throw path + " is not a valid json.";
				int c= 5;
			}
			// parse use reference of stream, that's annoying because that mean
			// I have to keep stream object alive in stack until i extract data fromp json ...
			// and connot use a load_json method :/
			// json load_json(const std::string& path);
		}

		const ExternalConstants::Config& get_config()
		{
			return config;
		}

		const ExternalConstants::GameDesign& get_gd()
		{
			return game_design;
		}

		const ExternalConstants::LevelDesign& get_ld()
		{
			return level_design;
		}
	}
}
