#include "framework/BWMeshLoader.h"

BWMeshLoader::BWMeshLoader()
{

}

BWMeshLoader::~BWMeshLoader()
{

}

BWMeshLoader* BWMeshLoader::getInstance()
{
	if(mInstance == 0)
	{
		mInstance = new BWMeshLoader();
	}
	return mInstance;
}