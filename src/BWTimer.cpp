#include "BWTimer.h"
#include "SDL2/SDL.h"
BWTimer* BWTimer::mInstance = 0;

BWTimer::BWTimer()
{
	mEclapseFrame = 0;
	mLastTime = 0;
	mEclapseTime = 0;
	mLastFrame = 0;
}

BWTimer* BWTimer::getInstance()
{
	if (mInstance == 0)
	{
		mInstance = new BWTimer();
	}
	return mInstance;
}

BWTimer::~BWTimer()
{

}

long BWTimer::GetFPS()
{
	return mLastFrame;
}

void BWTimer::Frame()
{
	mEclapseFrame++;
	mEclapseTime = SDL_GetTicks() - mLastTime;
	if (mEclapseTime >= 1000)
	{
		mLastTime = SDL_GetTicks();
		mLastFrame = mEclapseFrame;
		mEclapseFrame = 0;
	}
}