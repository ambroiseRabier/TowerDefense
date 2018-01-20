#pragma once
#ifndef MINION_HPP
#define MINION_HPP
namespace TowerDefense
{
	namespace Game
	{
		namespace Map
		{
			/**
			 * \brief 
			 * Enum representing the minion type, should be unique to class.
			 */
			enum MinionId
			{
				Peon,
				Tank,
				Heal,
			};

			/**
			 * \brief 
			 * For loading from file.
			 * (you should use " " column separator)
			 */
			static std::unordered_map<std::string, MinionId> stringToMinionIdEnum = {
				{"Peon", Peon}, {"P", Peon},
				{"Tank", Tank}, {"T", Tank},
				{"Heal", Heal}, {"H", Heal},
			};

			class Minion
			{
			public:
				Minion();
				~Minion();
			};
		}
	}
}
#endif