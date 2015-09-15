#include "framework/BWMeshLoader.h"

BWMeshLoader* BWMeshLoader::mInstance = 0;

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

void BWMeshLoader::Debug(const char* content)
{
	std::cout<<content<<std::endl;
}