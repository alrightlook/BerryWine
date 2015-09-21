#ifndef BWAPPLICATION_HEADER
#include "SDL2/SDL.h"
#include "BWWindow.h"
#include "BWScene.h"
#include "GL/glew.h"
#include <functional>

#include "BWCommonDef.h"

class BW_DLL BWApplication
{
public:
	BWApplication(BWWindow* mainWindow);
	~BWApplication();
	void run();
	void loadScene(BWScene* scene);
	void KeyEvent(SDL_Event* event);
	void MouseButtonEvent(SDL_Event* event);
private:
	bool mQuit;
	BWScene* mCurrentScene;
	BWWindow* mMainWindow;
};

#endif