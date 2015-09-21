#ifndef BWFBXMESH_HEADER
#define BWFBXMESH_HEADER

#ifdef BUILDING_BERRYWINE_DLL
#define BW_DLL __declspec(dllexport)
#else
#define BW_DLL __declspec(dllimport)
#endif

#include <string>

class BW_DLL BWFbxMesh
{
public:
	BWFbxMesh(std::string name, int meshNum, int indicesNum);
	~BWFbxMesh();
	float* GetMesh();
	int* GetIndices();

	void setMeshValue(int index, float val);
	void setIndiceValue(int index, int val);

	void DisplayMesh();
	void DisplayIndices();

	void Draw();
private:
	float* mMesh;
	int* mIndices;
	std::string mName;

	int mMeshNum;
	int mIndicesNum;
};
#endif