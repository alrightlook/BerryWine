#include "BWApplication.h"
#include "BWTimer.h"

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
	
	while(!mQuit)
	{
		BWTimer::getInstance()->Frame();
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