#include "BWScene.h"
#include "SDL2/SDL.h"

int BWScene::mEntityCount = 0;

BWScene::BWScene()
{

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

void BWScene::addEntity(BWEntity* entity)
{
	mEntityCount++;
	entity->Init();
	mMapEntities.insert(std::pair<int, BWEntity*>(mEntityCount, entity));
}

int BWScene::getEntityCount()
{
	return mEntityCount;
}