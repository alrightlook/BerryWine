#include <iostream>
#include "BWApplication.h"
#include "BWScene.h"
#include "BWTriangle.h"
#include "BWshader.h"
#include "BWCommon.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(int argc, char* argv[])
{
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 1.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//BWCommon::DebugOutputMatrix(viewMatrix);
	BWApplication app(new BWWindow("Demo", 100, 100, 640, 480));
	BWScene* mainScene = new BWScene();
	BWTriangle* mainentity = new BWTriangle();
	mainScene->addEntity(mainentity);
	app.loadScene(mainScene);
	app.run();
	delete mainScene;
	delete mainentity;
	return 0;
}