#pragma once
#ifndef ASSETS_CONFIG_HPP
#define ASSETS_CONFIG_HPP

namespace TowerDefense
{
	namespace Constants
	{
		/**
		 * \brief 
		 * Any configuration that is only graphic (or mostly liek death time for minion)
		 * and some constants of assets size.
		 */
		namespace AssetsConfig
		{
			/**
			 * \brief All tiles should do 50x50 in size.
			 */
			const unsigned int tile_size = 50;
			const sf::Vector2f tile_size_half_vec(tile_size/2.f, tile_size/2.f);
			/**
			 * \brief Only visual.
			 */
			const float minion_death_delay = 1.f;
		}
	}
}
#endif
