#pragma once
#ifndef SCREEN_HPP
#define SCREEN_HPP
/**
 * \brief 
 * You should handle your childrens pointer yourself.
 * SeeAlso: https://github.com/SFML/SFML/wiki/Tutorial:-Manage-different-Screens
 */
class Screen
{
public:
	Screen();
	~Screen();
	/**
	 * \brief 
	 * Create all childrens.
	 */
	virtual void init();
	/**
	 * \brief 
	 * Open screen.
	 */
	virtual void open();
	/**
	 * \brief 
	 * Close screen.
	 */
	virtual void close();
	bool get_is_open();
private:
	bool is_open;
};
#endif

