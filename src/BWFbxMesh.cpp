#include "BWFbxMesh.h"

BWFbxMesh::BWFbxMesh()
{

}

BWFbxMesh::~BWFbxMesh()
{

}

float* BWFbxMesh::GetMesh()
{
	return mMesh;
}

int* BWFbxMesh::GetIndices()
{
	return mIndices;
}