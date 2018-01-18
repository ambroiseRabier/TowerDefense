#pragma once

namespace TowerDefense
{
	namespace GameEngine
	{
		enum ColligerTag{ Minion, Castle, TowerShoot};

		class Collider
		{
		public:
			Collider();
			~Collider();
			bool mouse_enabled = true;
			bool gameobject_enabled = true;
			ColligerTag tag;
		};
	}
}
