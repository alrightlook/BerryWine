#include "framework/BWPointLight.h"
#include "framework/BWLightManager.h"

BWPointLight::BWPointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec4 position)
{
	SetAmbientColor(ambient);
	SetDiffuseColor(diffuse);
	SetSpecularColor(specular);

	SetPosition(position);
	BWLightManager::getInstance()->AddLight(this);
}

BWPointLight::~BWPointLight()
{
	
}

void BWPointLight::Frame()
{

}

void BWPointLight::Init()
{

}