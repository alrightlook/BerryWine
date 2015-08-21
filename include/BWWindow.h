#ifndef BWWINDOW_HEADER
#define BWWINDOW_HEADER
#include "SDL2/SDL.h"
class BWWindow
{
public:
	BWWindow(const char* title, int x, int y, int w, int h);
	~BWWindow();

	void run();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRender;
};

#endif