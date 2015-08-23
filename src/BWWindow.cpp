#include "BWWindow.h"

BWWindow::BWWindow(const char* title, int x, int y, int w, int h)
{
	mWindow = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	mGLContext = SDL_GL_CreateContext(mWindow);
}

BWWindow::~BWWindow()
{
	if (mGLContext != 0)
	{
		SDL_GL_DeleteContext(mGLContext);
	}
	if (mWindow != 0)
	{
		SDL_DestroyWindow(mWindow);
	}
	if (mRender != 0)
	{
		SDL_DestroyRenderer(mRender);
	}
}

void BWWindow::run()
{
	if (mRender != 0)
	{
		//SDL_RenderPresent(mRender);		//use for 2d?
	}
	SDL_GL_SwapWindow(mWindow);
}