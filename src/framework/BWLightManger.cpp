#include "framework\BWLightManager.h"

BWLightManager* BWLightManager::mInstance = 0;
std::map<std::string, BWAbstractLight*> BWLightManager::mMapLights = std::map<std::string, BWAbstractLight*>();

BWLightManager::BWLightManager()
{
}

BWLightManager::~BWLightManager()
{
}

BWAbstractLight* BWLightManager::getLight(std::string name)
{
	return mMapLights.find(name)->second;
}

BWLightManager* BWLightManager::getInstance()
{
	if (mInstance == 0)
	{
		mInstance = new BWLightManager();
	}
	return mInstance;
}

void BWLightManager::AddLight(BWAbstractLight* light)
{
	if (mMapLights.find(light->name) == mMapLights.end())
	{
		mMapLights.insert(std::pair<std::string, BWAbstractLight*>(light->name, light));
	}
}


