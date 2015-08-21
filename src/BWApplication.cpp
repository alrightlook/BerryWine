#include "BWApplication.h"

BWApplication::BWApplication(BWWindow* mainWindow)
{
	mQuit = false;
	mMainWindow = mainWindow;
}

BWApplication::~BWApplication()
{

}

void BWApplication::run()
{
	SDL_Event event;
	while(!mQuit)
	{
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