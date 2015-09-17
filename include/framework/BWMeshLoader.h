#ifndef BWMESHLOADER_HEADER
#define BWMESHLOADER_HEADER

#ifdef BUILDING_BERRYWINE_DLL
#define BW_DLL __declspec(dllexport)
#else
#define BW_DLL __declspec(dllimport)
#endif

#include <iostream>

class BW_DLL BWMeshLoader
{
public:
	static BWMeshLoader* getInstance();
	static void Debug(const char* content);
	static void LoadFBXScene(const char* filename);
private:
	static BWMeshLoader* mInstance;
	BWMeshLoader();
	~BWMeshLoader();
};
#endif