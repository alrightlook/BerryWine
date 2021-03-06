#include "framework/BWFbxLoader.h"
#include "BWCommon.h"
#include "BWScene.h"
#include <iostream>

BWFbxLoader::BWFbxLoader()
{
	name = std::string("Mesh") + BWCommon::intToString(BWScene::getEntityCount());
	mType = eTriangle;
}


BWFbxLoader::~BWFbxLoader()
{
	
}


void BWFbxLoader::DrawMeshes()
{
	if (mShader == 0)
	{
		return;
	}
	//mShader->Use();
	for (int i = 0 ; i < mMeshes.size(); i++)
	{
		mMeshes[i]->Frame();
	}
	//mShader->Unuse();
}

void BWFbxLoader::Init()
{
	return;
	for(int i = 0; i < mMeshes.size(); i++)
	{
		mMeshes[i]->Init();
	}
}

void BWFbxLoader::Frame()
{
	//mShader->Use();
	for (int i = 0 ; i < mMeshes.size(); i++)
	{
		mMeshes[i]->Frame();
	}
	//mShader->Unuse();
}