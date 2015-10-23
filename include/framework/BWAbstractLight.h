#ifndef BW_ABSTRACT_LIGHT
#define BW_ABSTRACT_LIGHT
#include "BWEntity.h"
#include "glm\glm.hpp"
#include <vector>

class BWAbstractLight : public BWEntity
{
public:
	BWAbstractLight();
	~BWAbstractLight();

	virtual void Init();
	virtual void Frame();

	std::vector<float> GetAmbientColor();
	std::vector<float> GetDiffuseColor();
	std::vector<float> GetSpecularColor();

	void SetAmbientColor(glm::vec3 ambientColor);
	void SetDiffuseColor(glm::vec3 diffuseColor);
	void SetSpecularColor(glm::vec3 specularColor);

protected:
	bool mEnable;
private:
	glm::vec4 mPostion;
	glm::vec3 mAmbientColor;
	glm::vec3 mDiffuseColor;
	glm::vec3 mSpecularColor;
};
#endif