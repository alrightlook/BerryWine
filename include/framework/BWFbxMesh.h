#ifndef BWFBXMESH_HEADER
#define BWFBXMESH_HEADER

#ifdef BUILDING_BERRYWINE_DLL
#define BW_DLL __declspec(dllexport)
#else
#define BW_DLL __declspec(dllimport)
#endif

#include <string>
#include "BWEntity.h"
#include <vector>

class BW_DLL BWFbxMesh : public BWEntity
{
public:
	BWFbxMesh(std::string name, int meshNum, int indicesNum);
	~BWFbxMesh();
	float* GetMesh();
	GLuint* GetIndices();
	void setMeshValue(std::vector<float> val);

	void setIndiceValue(std::vector<GLuint> val);

	void setNormal(float val);

	float* getMeshVertex();
	float* getNormals();
	GLuint* getIndices();

	void DisplayMesh();
	void DisplayIndices();

	void Init();
	void Frame();
private:

	std::vector<float> mMesh;
	std::vector<GLuint> mIndices;
	std::vector<float> mNormals;
	std::string mName;

	int mMeshNum;
	int mIndicesNum;
};
#endif