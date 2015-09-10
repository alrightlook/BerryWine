#include <iostream>
#include "BWApplication.h"
#include "BWScene.h"
#include "BWTriangle.h"
#include "BWshader.h"
#include "BWCommon.h"
#include "BWCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(int argc, char* argv[])
{
	BWApplication app(new BWWindow("Demo", 100, 100, 640, 480));
	BWScene* mainScene = new BWScene();
	BWCamera* mainCamera = new BWCamera();
	BWTriangle* mainentity = new BWTriangle();
	mainScene->addEntity(mainentity);
	mainScene->addCamera(mainCamera);
	app.loadScene(mainScene);
	app.run();
	delete mainScene;
	delete mainentity;
	return 0;
}