#ifndef BWFBXMESH_HEADER
#define BWFBXMESH_HEADER

#ifdef BUILDING_BERRYWINE_DLL
#define BW_DLL __declspec(dllexport)
#else
#define BW_DLL __declspec(dllimport)
#endif

#include <string>
#include "BWEntity.h"

class BW_DLL BWFbxMesh : public BWEntity
{
public:
	BWFbxMesh(std::string name, int meshNum, int indicesNum);
	~BWFbxMesh();
	float* GetMesh();
	int* GetIndices();

	void setMeshValue(int index, float val);
	void setIndiceValue(int index, int val);
	void setNormal(int index, float val);

	float* getMeshVertex();
	float* getNormals();
	int* getIndices();

	void DisplayMesh();
	void DisplayIndices();

	void Init();
	void Frame();
private:
	float* mMesh;
	int* mIndices;
	float* mNormals;
	std::string mName;

	int mMeshNum;
	int mIndicesNum;
};
#endif