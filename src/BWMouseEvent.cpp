#include "BWMouseEvent.h"
#include <iostream>

BWMouseEvent* BWMouseEvent::mInstance = 0;

std::vector<std::function<void(SDL_Event*)>> BWMouseEvent::mEventList;

BWMouseEvent::BWMouseEvent()
{

}

BWMouseEvent::~BWMouseEvent()
{

}

BWMouseEvent* BWMouseEvent::getInstance()
{
	if(mInstance == 0)
	{
		mInstance = new BWMouseEvent();
	}
	return mInstance;
}

void BWMouseEvent::RegisterEvent(std::function<void(SDL_Event*)> callback)
{
	mEventList.push_back(callback);
}

void BWMouseEvent::DispatchEvent(SDL_Event* event)
{
	for (int i = 0; i < mEventList.size(); i++)
	{
		mEventList[i](event);
	}
}