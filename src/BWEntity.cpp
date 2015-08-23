#include "BWEntity.h"
#include "BWScene.h"
#include "BWCommon.h"
#include "SDL2/SDL.h"
#include "GL/gl.h"

BWEntity::BWEntity()
{
	name = std::string("Entity") + BWCommon::intToString(BWScene::getEntityCount());
}

BWEntity::~BWEntity()
{
	
}

void BWEntity::Init()
{

}

void BWEntity::Frame()
{
	
}


int BWEntity::getID()
{
	return id;
}