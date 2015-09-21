#ifndef BWFBX_LOADER_HEADRE
#define BWFBX_LOADER_HEADRE
#include "framework/BWFbxMesh.h"
#include <vector>
#include "BWShader.h"
#include "BWCommonDef.h"

class BW_DLL BWFbxLoader
{
public:
	BWFbxLoader();
	~BWFbxLoader();
	std::vector<BWFbxMesh*> mMeshes;

	void DrawMeshes(BWShader* shader);
private:

};
#endif