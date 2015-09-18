#ifndef BWFBX_LOADER_HEADRE
#define BWFBX_LOADER_HEADRE
#include "framework/BWFbxMesh.h"
#include <vector>

#ifdef BUILDING_BERRYWINE_DLL
#define BW_DLL __declspec(dllexport)
#else
#define BW_DLL __declspec(dllimport)
#endif

class BW_DLL BWFbxLoader
{
public:
	BWFbxLoader();
	~BWFbxLoader();
	std::vector<BWFbxMesh*> mMeshes;
private:

};
#endif