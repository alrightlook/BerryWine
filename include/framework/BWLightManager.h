#ifndef BW_LIGHT_MANAGER
#define BW_LIGHT_MANAGER

#include "framework\BWAbstractLight.h"
#include <map>
#include <string>
#include <vector>

class BWLightManager
{

public:
	BWLightManager* getInstance();
	~BWLightManager();
	void AddLight(BWAbstractLight* light);
	BWAbstractLight* getLight(std::string name);
	std::vector<BWAbstractLight*> getLightList();

private:
	BWLightManager();
	static BWLightManager* mInstance;
	static std::vector<BWAbstractLight*> mVecLights;
	static std::map<std::string, BWAbstractLight*> mMapLights;
};

#endif;