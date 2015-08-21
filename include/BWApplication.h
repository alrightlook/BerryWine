#ifndef BWAPPLICATION_HEADER
#include "SDL2/SDL.h"
#include "BWWindow.h"

class BWApplication
{
public:
	BWApplication(BWWindow* mainWindow);
	~BWApplication();
	void run();
private:
	bool mQuit;
	BWWindow* mMainWindow;
};

#endif