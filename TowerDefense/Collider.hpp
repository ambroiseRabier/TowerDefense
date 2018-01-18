#pragma once
#ifndef COLLIDER_HPP
#define COLLIDER_HPP
namespace TowerDefense
{
	namespace GameEngine
	{

		class Collider
		{
		public:
			enum class Tag
			{
				None=0,
				UI=1, 
				Minion=2, 
				Castle=3, 
				TowerShoot=4
			};
			Collider();
			~Collider();
			bool mouse_enabled = true;
			bool gameobject_enabled = true;
			Tag tag;
		};
	}
}
#endif

