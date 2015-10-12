#ifndef BW_LIGHT_MANAGER
#define BW_LIGHT_MANAGER

#include "framework\BWAbstractLight.h"
#include <map>
#include <string>

class BWLightManager
{

public:
	BWLightManager* getInstance();
	~BWLightManager();
	void AddLight(BWAbstractLight* light);
	BWAbstractLight* getLight(std::string name);
private:
	BWLightManager();
	static BWLightManager* mInstance;

	static std::map<std::string, BWAbstractLight*> mMapLights;
};

#endif;