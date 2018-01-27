#pragma once
#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include "../../Circle.hpp"

namespace TowerDefense
{
	namespace GameEngine
	{

		/**
		 * \brief 
		 * Collider, similar to unity collider, the constructor called define the type of collider you use.
		 * The type can be a rectangle, a circle, ...
		 * The tag will determine accroding to Config settings between wich gameobjects the collisions is tested.
		 */
		class Collider
		{
		public:
			enum class Tag
			{
				None=0,
				UI=1, 
				Minion=2, 
				Castle=3, 
				Projectile=4,
				Tower=5
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

			static std::string Type_to_string(Type type)
			{
				switch (type)
				{
				case Collider::Type::None: return "None";
				case Collider::Type::Dot: return "Dot";
				case Collider::Type::Rect: return "Rect";
				case Collider::Type::Circle: return "Circle";
				case Collider::Type::SpriteRect: return "SpriteRect";
				case Collider::Type::SpriteCircle: return "SpriteCircle";
				case Collider::Type::SpritePixelPerfect: return "SpritePixelPerfect";
				default: return "Unknow";
				}
			}	

			/**
			 * \brief This is the default constructor. But you better add a Tag other then Tag::None.
			 */
			Collider(Tag newTag = Tag::None);
			Collider(sf::Vector2f newDot, Tag newTag = Tag::None);
			Collider(sf::FloatRect newRect, Tag newTag = Tag::None);
			Collider(Circle newCircle, Tag newTag);

			/**
			 * \brief 
			 * Note: if you intend on using pixel perfect collision, 
			 * you can pre-create the bitmask with Collision::CreateTextureAndBitmask method.
			 * \param newSprite 
			 * \param newTag
			 * \param newType Valid type are SpriteRect, SpriteCircle, SpritePixelPerfect
			 */
			Collider(const sf::Sprite& newSprite, Tag newTag = Tag::None, Type newType = Type::SpriteRect);
			~Collider();
			bool mouse_enabled = true;
			bool gameobject_enabled = true;
			Tag tag = Tag::None;
			Type get_type() const;

			// I could use a pointer bellow, since the value can be nullptr actually.
			// But if you do call when it is nullptr, then you have made an error in your code logic,
			// And I do not wish to hide that.
			/**
			 * \brief Make sure your colldier is of type dot before calling this.
			 * \return 
			 */
			const sf::Vector2f& get_dot() const;

			/**
			 * \brief Make sure your colldier is of type rect before calling this.
			 * \return 
			 */
			const sf::FloatRect& get_rect() const;

			/**
			 * \brief Make sure your colldier is of type SpriteRect or SpriteCircle or SpritePixelPerfect before calling this.
			 * \return 
			 */
			const sf::Sprite& get_sprite() const;

			const Circle& get_circle() const;
		private:
			Type type;
			sf::FloatRect rect;
			sf::Vector2f dot;
			Circle circle;
			const sf::Sprite* sprite;
		};
	}
}
#endif

