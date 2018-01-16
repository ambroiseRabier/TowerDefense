#pragma once
#include <SFML/Graphics/Drawable.hpp>

namespace TowerDefense
{
	namespace Utils
	{
		class BaseMonoBehaviour
		{
		public:
			BaseMonoBehaviour();
			~BaseMonoBehaviour();
			/// Start BaseMonoBehaviour, called by the one instanciating him. You need to call base.start().
			virtual void start();
		protected:
			/// Called by constructor
			virtual void awake();
			/// Initialize variables
			virtual void initVar();
			virtual void listenToEvents();
			virtual void unListenToEvents();
			/// Called every frame.
			virtual void update();
			/// Reset state (for pooling).
			virtual void recycle();
			/// Called by decontructor.
			virtual void onDestroy();
			//sf::Drawable
			//sf:Transform
		};

	}
}
