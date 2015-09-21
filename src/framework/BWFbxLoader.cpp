#include "framework/BWFbxLoader.h"

BWFbxLoader::BWFbxLoader()
{

}


BWFbxLoader::~BWFbxLoader()
{
	
}


void BWFbxLoader::DrawMeshes(BWShader* shader)
{
	shader->Use();
	for (int i = 0 ; i < mMeshes.size(); i++)
	{
		mMeshes[i]->Frame();
	}
	shader->Unuse();
}

void BWFbxLoader::Init()
{
}

void BWFbxLoader::Frame()
{
}