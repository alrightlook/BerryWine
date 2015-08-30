#include <iostream>
#include "BWApplication.h"
#include "BWScene.h"
#include "BWEntity.h"
#include "BWshader.h"

int main(int argc, char* argv[])
{
	BWApplication app(new BWWindow("Haha", 100, 100, 640, 480));
	BWShader triangle("vert.vert", "frag.frag");
	BWScene* mainScene = new BWScene();
	BWEntity* mainentity = new BWEntity();
	mainScene->addEntity(mainentity);
	app.loadScene(mainScene);
	app.run();
	return 0;
}