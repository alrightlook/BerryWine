#include "framework/BWAbstractLight.h"

BWAbstractLight::BWAbstractLight()
{
	mEnable = true;
}

std::vector<float> BWAbstractLight::GetAmbientColor()
{
	std::vector<float> ac;
	ac.push_back(mAmbientColor.r);
	ac.push_back(mAmbientColor.g);
	ac.push_back(mAmbientColor.b);

	return ac;
}

std::vector<float> BWAbstractLight::GetDiffuseColor()
{
	std::vector<float> dc;
	dc.push_back(mDiffuseColor.r);
	dc.push_back(mDiffuseColor.g);
	dc.push_back(mDiffuseColor.b);

	return dc;
}

void BWAbstractLight::SetAmbientColor(glm::vec3 ambientColor)
{
	mAmbientColor = ambientColor;
}

void BWAbstractLight::SetDiffuseColor(glm::vec3 diffuseColor)
{
	mDiffuseColor = diffuseColor;
}

void BWAbstractLight::SetSpecularColor(glm::vec3 specularColor)
{
	mSpecularColor = specularColor;
}

std::vector<float> BWAbstractLight::GetSpecularColor()
{
	std::vector<float> sc;
	sc.push_back(mSpecularColor.r);
	sc.push_back(mSpecularColor.g);
	sc.push_back(mSpecularColor.b);

	return sc;

}

BWAbstractLight::~BWAbstractLight()
{

}

void BWAbstractLight::Init()
{
}

void BWAbstractLight::Frame()
{

}