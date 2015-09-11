#ifndef BW_KEYEVENT_HEADER
#define BW_KEYEVENT_HEADER

#include "SDL2/SDL.h"
#include <vector>
#include <functional>

class BWKeyEvent
{
private:
	BWKeyEvent();
	~BWKeyEvent();
	static BWKeyEvent* mInstance;
	static std::vector<std::function<void(SDL_Event*)>> mVecKeyEventList;
public:
	static BWKeyEvent* getInstance();
	void DispatchEvent(SDL_Event* event);
	void RegisterListener(std::function<void(SDL_Event*)> callback);
};
#endif