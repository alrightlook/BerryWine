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
		mMeshes[i]->Draw();
	}
	shader->Unuse();
}