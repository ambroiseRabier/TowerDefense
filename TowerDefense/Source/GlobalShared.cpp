#include "stdafx.h"
#include "../GlobalShared.hpp"
#include "Utils/Event.h"
#include "../Assets.hpp"
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

		void destroy()
		{
			delete default_font; default_font = nullptr;

			if (!stringToTexture.empty())
			{
				for (auto && pair : stringToTexture)
				{
					pair.second.reset(nullptr);
				}
				stringToTexture.clear();
			}
			
		}
	}
}
