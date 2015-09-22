#include "framework/BWFbxLoader.h"
#include "BWCommon.h"
#include "BWScene.h"

BWFbxLoader::BWFbxLoader()
{
	name = std::string("Triangle") + BWCommon::intToString(BWScene::getEntityCount());
	mType = eTriangle;
	mShader = new BWShader("vert.vert", "frag.frag");
}


BWFbxLoader::~BWFbxLoader()
{
	
}


void BWFbxLoader::DrawMeshes()
{
	mShader->Use();
	for (int i = 0 ; i < mMeshes.size(); i++)
	{
		mMeshes[i]->Frame();
	}
	mShader->Unuse();
}

void BWFbxLoader::Init()
{
}

void BWFbxLoader::Frame()
{
	mShader->Use();
	for (int i = 0 ; i < mMeshes.size(); i++)
	{
		mMeshes[i]->Frame();
	}
	mShader->Unuse();
}