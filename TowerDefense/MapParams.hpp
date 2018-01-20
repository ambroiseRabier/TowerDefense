#pragma once
#include "Tile.hpp"
#include "Minion.hpp"

namespace TowerDefense
{
	namespace Game
	{
		namespace Map
		{
			struct MinionWaveParams
			{
				MinionWaveParams(float delay_before_next, MinionId minion_id)
					: delay_before_next(delay_before_next),
					  minion_id(minion_id)
				{
				}

				const float delay_before_next;
				const MinionId minion_id;
			};

			/**
			 * \brief 
			 * Contains all parameters or a wave of minions.
			 */
			struct WaveParams
			{
				WaveParams(float delay_before_next, const std::vector<MinionWaveParams>& minion_params_vector)
					: delay_before_next(delay_before_next),
					  minion_params_vector(minion_params_vector)
				{
				}

				const float delay_before_next;
				const std::vector<MinionWaveParams> minion_params_vector{};
			};

			/**
			 * \brief 
			 * Contains all parameters of a map.
			 * others stuff, like mabiance, music, ...
			 */
			struct MapParams
			{
				MapParams(const float start_money,
						  const std::vector<std::vector<TileId>>& map_background_tile_array,
				          const std::vector<WaveParams>& wave_params_vector)
					: start_money(start_money),
					  map_background_tile_array(map_background_tile_array),
					  wave_params_vector(wave_params_vector)
					  
				{
				}

				const float start_money;
				/**
				 * \brief 
				 * Fixed size to 28 on x, 21 on y (should be choose according to default screen size and gd).
				 * We could use a vector to make the size variable. 
				 * No we use a vector because we need initializing list in Constants.
				 */
				const std::vector<std::vector<TileId>> map_background_tile_array;
				const std::vector<WaveParams> wave_params_vector{};
			};
		}
	}
}
