#include "BWScene.h"
#include "SDL2/SDL.h"
#include "BWCommon.h"

int BWScene::mEntityCount = 0;
BWScene* BWScene::mpCurrentScene = 0;

BWScene::BWScene()
{
	mPerspectiveMatrix = glm::perspective(60.0f * PI /180.0f ,640.0f / 480.0f, 0.1f, 1000.f);
	mpCurrentScene = this;
}

BWScene::~BWScene()
{

}

void BWScene::Frame()
{
	GLfloat background[] = {0.27f, 0.27f, 0.27f, 1.0f};
	glClearBufferfv(GL_COLOR, 0, background);

	std::map<int, BWEntity*>::iterator it;
	for(it = mMapEntities.begin(); it != mMapEntities.end(); ++it)
	{
		it->second->Frame();
	}

	std::map<int, BWCamera*>::iterator cameraIt;
	for(cameraIt = mMapCameras.begin(); cameraIt != mMapCameras.end(); ++cameraIt)
	{
		cameraIt->second->Frame();
	}
}

void BWScene::Init()
{
	std::map<int, BWEntity*>::iterator it;
	for(it = mMapEntities.begin(); it != mMapEntities.end(); ++it)
	{
		it->second->Init();
	}
}

void BWScene::addCamera(BWCamera* camera)
{
	if (camera == 0)
	{
		return;
	}
	mMapCameras.insert(std::pair<int, BWCamera*>(camera->getIndex(), camera));
}

glm::mat4 BWScene::getPerspectiveMatrix()
{
	return mPerspectiveMatrix;
}

BWScene* BWScene::getCurrentScene()
{
	return mpCurrentScene;
}

void BWScene::addEntity(BWEntity* entity)
{
	mEntityCount++;
	mMapEntities.insert(std::pair<int, BWEntity*>(mEntityCount, entity));
}

int BWScene::getEntityCount()
{
	return mEntityCount;
}