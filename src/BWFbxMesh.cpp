#include "framework/BWFbxMesh.h"
#include <iostream>

BWFbxMesh::BWFbxMesh(std::string name, int meshNum, int indicesNum)
{
	mName = name;
	mMesh = (float*) malloc(meshNum);
	mIndices = (int*) malloc(indicesNum);
	mNormals = (float*) malloc(indicesNum);

	this->name = name;
	this->mType = BWEntityType::eMesh;

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

void BWFbxMesh::setNormal(int index, float val)
{
	mNormals[index] = val;
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

float* BWFbxMesh::getMeshVertex()
{
	return mMesh;
}

float* BWFbxMesh::getNormals()
{
	return mNormals;
}

int* BWFbxMesh::getIndices()
{
	return mIndices;
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
	RegisterVertexData((void*)mMesh);
}

void BWFbxMesh::Frame()
{
	
}