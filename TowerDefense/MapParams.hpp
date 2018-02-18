#pragma once
#ifndef MAP_PARAMS_HPP
#define MAP_PARAMS_HPP
#include "Tile.hpp"
#include "Minion.hpp"

namespace TowerDefense
{
	namespace Game
	{
		struct MinionWaveParams
		{
			MinionWaveParams(){}

			MinionWaveParams(float delay_before_next, MinionId minion_id)
				: delay_before_next(delay_before_next),
				  minion_id(minion_id)
			{
			}

			float delay_before_next;
			MinionId minion_id;
		};

		inline void from_json(json j, MinionWaveParams& p) {
			try
			{
				p.delay_before_next = j.at("delay_before_next").get<float>();
				p.minion_id = Game::stringToMinionIdEnum.at(j.at("minion_id").get<std::string>());
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}

		/**
		 * \brief 
		 * Contains all parameters or a wave of minions.
		 */
		struct WaveParams
		{
			WaveParams(){}

			WaveParams(float delay_before_next, const std::vector<MinionWaveParams>& minion_params_vector)
				: delay_before_next(delay_before_next),
				  minion_params_vector(minion_params_vector)
			{
			}

			/**
			 * \brief This correpond to an additionnal delay after all minion wave has been played.
			 */
			float delay_before_next;
			std::vector<MinionWaveParams> minion_params_vector{};
		};

		inline void from_json(json j, WaveParams& p) {
			try
			{
				p.delay_before_next = j.at("delay_before_next").get<float>();
				p.minion_params_vector = j.at("minion_params_vector").get<std::vector<MinionWaveParams>>();
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}

		/**
		 * \brief 
		 * Contains all parameters of a map.
		 * others stuff, like mabiance, music, ...
		 */
		struct MapParams
		{
			MapParams(){};

			MapParams(const std::string name,
					  const unsigned int preparation_time,
					  const float start_money,
			          const std::vector<std::vector<TileId>>& map_background_tile_array,
			          const std::vector<WaveParams>& wave_params_vector)
				: name(name),
				  preparation_time(preparation_time),
				  start_money(start_money),
				  map_background_tile_array(map_background_tile_array),
				  wave_params_vector(wave_params_vector)

			{
			}

			std::string name;
			unsigned int preparation_time;
			float start_money;
			/**
			 * \brief 
			 * Fixed size to 28 on x, 21 on y (should be choose according to default screen size and gd).
			 * We could use a vector to make the size variable. 
			 * No we use a vector because we need initializing list in Constants.
			 */
			std::vector<std::vector<TileId>> map_background_tile_array;
			std::vector<WaveParams> wave_params_vector{};
		};

		
		inline void from_json(json j, MapParams& p) {
			// if one exception occur, multiple settings might use default.
			// solution would be use a try catch for every field.
			try
			{
				p.name = j.at("name").get<std::string>();
				p.preparation_time = j.at("preparation_time").get<unsigned int>();
				p.start_money = j.at("start_money").get<float>();

				auto temp_tile_array = j.at("map_background_tile_array").get<std::vector<std::vector<std::string>>>();
				for (const auto tileRow : temp_tile_array)
				{
					std::vector<TileId> row;
					for (const std::string tileId : tileRow)
					{
						row.push_back(Game::stringToTileIdEnum.at(tileId));
					}
					p.map_background_tile_array.push_back(row);
				}
				p.wave_params_vector = j.at("wave_params_vector").get<std::vector<WaveParams>>();
			}
			catch (json::exception& e)
			{
				std::cout << e.what() << '\n';
			}
		}
	}
}
#endif
