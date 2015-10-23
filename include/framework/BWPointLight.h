#ifndef BWPOINT_LIGHT_HEADER
#define BWPOINT_LIGHT_HEADER
#include "BWCommonDef.h"
#include "BWAbstractLight.h"
#include "glm/glm.hpp"

class BW_DLL BWPointLight : public BWAbstractLight
{
public:
	BWPointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~BWPointLight();

	void Init();
	void Frame();
private:
	
};
#endif