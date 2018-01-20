#pragma once
#ifndef TOWER_HPP
#define TOWER_HPP
/**
* \brief 
* Enum representing the tower type, should be unique to class.
*/
enum TowerId
{
	RockTower,
	FreezeTower,
	ExplosivTower,
};

/**
 * \brief 
 * Can only be placed on BuildableTile.
 */
class Tower
{
public:
	Tower();
	~Tower();
};
#endif

