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
	std::map<int, BWEntity*>::iterator it;
	for(it = mMapEntities.begin(); it != mMapEntities.end(); ++it)
	{
		it->second->Frame();
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