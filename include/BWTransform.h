#ifndef BWTRANSFORM_HEADER
#define BWTRANSFORM_HEADER

#include "BWCommonDef.h"
#include "glm/glm.hpp"

class BW_DLL BWTransform
{
public:
	BWTransform();
	~BWTransform();
	glm::mat4 Transform();

	void Translate(glm::vec3 translateVector);
	void Scale(glm::vec3 scaleVector);
private:
	glm::mat4 mTransfomMatrix;
	glm::vec3 mPostion;
	glm::vec3 mScale;
};
#endif