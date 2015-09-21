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
	BWFbxLoader meshLoader;
	BWMeshLoader::getInstance()->Debug("This is mesh loader debug info");
	BWMeshLoader::getInstance()->LoadFBXScene("cube.fbx", &meshLoader);
	for (int i = 0; i < meshLoader.mMeshes.size(); i++)
	{
		//meshLoader->mMeshes[i]->DisplayMesh();
		//meshLoader->mMeshes[i]->DisplayIndices();
	}
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