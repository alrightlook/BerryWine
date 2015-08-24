#include <iostream>
#include "BWApplication.h"
#include "BWScene.h"
#include "BWEntity.h"

int main(int argc, char* argv[])
{
	BWApplication app(new BWWindow("Haha", 100, 100, 640, 480));
	BWScene* mainScene = new BWScene();
	BWEntity* mainentity = new BWEntity();
	mainScene->addEntity(mainentity);
	app.loadScene(mainScene);
	app.run();
	delete mainScene;
	delete mainentity;
	return 0;
}