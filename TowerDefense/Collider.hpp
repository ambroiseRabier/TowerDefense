#pragma once

namespace TowerDefense
{
	namespace GameEngine
	{

		class Collider
		{
		public:
			enum Tag{ Minion, Castle, TowerShoot};
			Collider();
			~Collider();
			bool mouse_enabled = true;
			bool gameobject_enabled = true;
			Tag tag;
		};
	}
}
