#pragma once
#ifndef FPS_HPP
#define FPS_HPP
#include <SFML/System/Clock.hpp>

class FPS
{ 
public:
	/// @brief Constructor with initialization.
	///
	FPS() : mFrame(0), mFps(0) {}

	/// @brief Update the frame count.
	/// 
	void update();

	/// @brief Get the current FPS count.
	/// @return FPS count.
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;
};

void FPS::update()
{
	if(mClock.getElapsedTime().asSeconds() >= 1.f)
	{
		mFps = mFrame;
		mFrame = 0;
		mClock.restart();
	}
 
	++mFrame;
}

#endif