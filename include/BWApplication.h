#ifndef BWAPPLICATION_HEADER
#include "SDL2/SDL.h"
#include "BWWindow.h"
#include "BWScene.h"
#include "GL/glew.h"

class BWApplication
{
public:
	BWApplication(BWWindow* mainWindow);
	~BWApplication();
	void run();
	void loadScene(BWScene* scene);
private:
	bool mQuit;
	BWScene* mCurrentScene;
	BWWindow* mMainWindow;
};

#endif