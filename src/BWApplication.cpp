#include "BWApplication.h"

BWApplication::BWApplication(BWWindow* mainWindow)
{
	mQuit = false;
	mMainWindow = mainWindow;
}

BWApplication::~BWApplication()
{
	if (mMainWindow != 0)
	{
		delete mMainWindow;
		mMainWindow = 0;
	}
	SDL_Quit();
}

void BWApplication::run()
{
	SDL_Event event;
	long eclapseFrame = 0;
	long eclapseTime = 0;
	long lastTime = 0;
	while(!mQuit)
	{
		eclapseFrame++;
		eclapseTime = SDL_GetTicks() - lastTime;
		if (eclapseTime >= 1000)
		{
			lastTime = SDL_GetTicks();
			SDL_Log("%d", eclapseFrame);
			eclapseFrame = 0;
		}
		
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			mQuit = true;
		}
		else {
			mMainWindow->run();
		}
		
	}
}