#include "BWWindow.h"

BWWindow::BWWindow(const char* title, int x, int y, int w, int h)
{
	mWindow = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	mRender = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
}

BWWindow::~BWWindow()
{

}

void BWWindow::run()
{
	if (mRender != 0)
	{
		SDL_RenderPresent(mRender);
	}
}