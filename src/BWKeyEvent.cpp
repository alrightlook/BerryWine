#include "BWKeyEvent.h"

BWKeyEvent* BWKeyEvent::mInstance = 0;
std::vector<std::function<void(SDL_Event*)>> BWKeyEvent::mVecKeyEventList;
BWKeyEvent::BWKeyEvent()
{

}


BWKeyEvent::~BWKeyEvent()
{

}

BWKeyEvent* BWKeyEvent::getInstance()
{
	if (mInstance == 0)
	{
		mInstance = new BWKeyEvent();
	}
	return mInstance;

}

void BWKeyEvent::DispatchEvent(SDL_Event* event)
{
	for(int i = 0; i < mVecKeyEventList.size(); i++)
	{
		mVecKeyEventList[i](event);
	}
}

void BWKeyEvent::RegisterListener(std::function<void(SDL_Event*)> callback)
{
	mVecKeyEventList.push_back(callback);
}