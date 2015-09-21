#include <iostream>
#include "BWApplication.h"
#include "BWScene.h"
#include "BWTriangle.h"
#include "BWshader.h"
#include "BWCommon.h"
#include "BWCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "framework/BWMeshLoader.h"
#include "framework\BWFbxLoader.h"

int main(int argc, char* argv[])
{
	BWApplication app(new BWWindow("Demo", 100, 100, 1024, 768));
	BWScene* mainScene = new BWScene();
	BWCamera* mainCamera = new BWCamera();
	BWTriangle* mainentity = new BWTriangle();
	BWFbxLoader meshLoader;
	BWMeshLoader::getInstance()->LoadFBXScene("cube.fbx", &meshLoader);

	app.loadScene(mainScene);
	app.run();

	return 0;
}