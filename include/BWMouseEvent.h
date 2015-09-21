#ifndef BWMOUSE_HEADER
#define BWMOUSE_HEADER

#include "SDL2/SDL.h"
#include <functional>
#include <vector>

#include "BWCommonDef.h"

class BW_DLL BWMouseEvent
{
public:
	static BWMouseEvent* getInstance();
	static void RegisterEvent(std::function<void(SDL_Event*)> callback);
	static void DispatchEvent(SDL_Event* event);
private:
	static BWMouseEvent* mInstance;
	static std::vector<std::function<void(SDL_Event*)>> mEventList;
	BWMouseEvent();
	~BWMouseEvent();
};

#endif
