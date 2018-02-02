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

		sf::Texture* menu_background;
		sf::Texture* missing_texture_tile_texture;
		sf::Texture* hpBar_background_texture;
		sf::Texture* hpBar_jauge_texture;

		sf::Texture* level1_btn_texture;
		sf::Texture* level2_btn_texture;
		sf::Texture* level3_btn_texture;
		sf::Texture* tower1_btn_texture;
		sf::Texture* tower2_btn_texture;
		sf::Texture* tower3_btn_texture;

		sf::Texture* castle_death_texture;
		sf::Texture* next_level_btn_texture;

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
			delete menu_background; menu_background = nullptr;
			delete missing_texture_tile_texture; missing_texture_tile_texture = nullptr;
			delete hpBar_background_texture; hpBar_background_texture = nullptr;
			delete hpBar_jauge_texture; hpBar_jauge_texture = nullptr;

			delete level1_btn_texture; level1_btn_texture = nullptr;
			delete level2_btn_texture; level2_btn_texture = nullptr;
			delete level3_btn_texture; level3_btn_texture = nullptr;
			delete tower1_btn_texture; tower1_btn_texture = nullptr;
			delete tower2_btn_texture; tower2_btn_texture = nullptr;
			delete tower3_btn_texture; tower3_btn_texture = nullptr;

			delete castle_death_texture; castle_death_texture = nullptr;
			delete next_level_btn_texture; next_level_btn_texture = nullptr;


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
