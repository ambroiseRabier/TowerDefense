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
			enum class Type
			{
				None=0,
				Dot=1,
				Rect=2,
				Circle=3,
				SpriteRect=4,
				SpriteCircle=5,
				SpritePixelPerfect=6,
				
			};
			Collider();
			Collider(std::unique_ptr<sf::FloatRect> newRect, Tag tag = Tag::None);
			~Collider();
			bool mouse_enabled = true;
			bool gameobject_enabled = true;
			Tag tag = Tag::None;
			Type get_type() const;
			sf::FloatRect& get_rect() const;
		private:
			Type type;
			std::unique_ptr<sf::FloatRect> rect;
		};
	}
}
#endif

