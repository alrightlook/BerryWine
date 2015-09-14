#include "BWApplication.h"
#include "BWTimer.h"
#include "GL/gl.h"
#include "BWKeyEvent.h"
#include "BWMouseEvent.h"

#include <stdio.h>
#include <iostream>
#include <functional>

BWApplication::BWApplication(BWWindow* mainWindow)
{
	mQuit = false;
	mMainWindow = mainWindow;
	glewInit();
	const GLubyte* glVersion = glGetString(GL_VERSION);
	printf("OpenGL Version %s", glVersion);

	using namespace std::placeholders;
	BWKeyEvent::getInstance()->RegisterListener(std::bind(&BWApplication::KeyEvent, this, _1));
	BWMouseEvent::getInstance()->RegisterEvent(std::bind(&BWApplication::MouseButtonEvent, this, _1));
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
		if (mCurrentScene != 0)
		{
			mCurrentScene->Frame();
		}
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			mQuit = true;
		}
		else {
			mMainWindow->run();
		}
       	BWKeyEvent::getInstance()->DispatchEvent(&event);

        if( event.button.type == SDL_MOUSEBUTTONUP )
        {
        	BWMouseEvent::getInstance()->DispatchEvent(&event);
        }
        if (event.button.type == SDL_MOUSEMOTION)
        {
        	BWMouseEvent::getInstance()->DispatchEvent(&event);
        }
    }
}

void BWApplication::loadScene(BWScene* scene)
{
	mCurrentScene = scene;
	if (mCurrentScene != 0)
	{
		mCurrentScene->Init();
	}
}

void BWApplication::KeyEvent(SDL_Event* event)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
	    mQuit = true;
	}
}

void BWApplication::MouseButtonEvent(SDL_Event* event)
{
	
}