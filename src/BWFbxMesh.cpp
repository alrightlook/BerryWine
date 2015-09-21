#include "framework/BWFbxMesh.h"
#include <iostream>

BWFbxMesh::BWFbxMesh(std::string name, int meshNum, int indicesNum)
{
	mName = name;
	mMesh = (float*) malloc(meshNum);
	mIndices = (int*) malloc(indicesNum);

	mMeshNum = meshNum;
	mIndicesNum = indicesNum;
}

BWFbxMesh::~BWFbxMesh()
{
	free(mMesh);
	free(mIndices);
}

float* BWFbxMesh::GetMesh()
{
	return mMesh;
}

int* BWFbxMesh::GetIndices()
{
	return mIndices;
}

void BWFbxMesh::setMeshValue(int index, float val)
{
	mMesh[index] = val;
}

void BWFbxMesh::setIndiceValue(int index, int val)
{
	mIndices[index] = val;
}

void BWFbxMesh::DisplayMesh()
{
	for (int i = 0; i < mMeshNum; i++ )
	{
		std::cout<<mMesh[i]<<" ";
	}
}

void BWFbxMesh::DisplayIndices()
{
	for (int i =0; i < mIndicesNum; i++)
	{
		std::cout<<mIndices[i]<<std::endl;
	}
}

void BWFbxMesh::Init()
{

}

void BWFbxMesh::Frame()
{

}