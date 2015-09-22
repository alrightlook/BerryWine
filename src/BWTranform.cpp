#include "BWTransform.h"
#include "glm/gtc/matrix_transform.hpp"

BWTransform::BWTransform()
{
	mTransfomMatrix = glm::mat4();
}

BWTransform::~BWTransform()
{

}

glm::mat4 BWTransform::Transform()
{
	return mTransfomMatrix;
}

void BWTransform::Translate(glm::vec3 translateVector)
{
	mTransfomMatrix = glm::translate(mTransfomMatrix, translateVector);
}

void BWTransform::Scale(glm::vec3 scaleVector)
{
	mTransfomMatrix = glm::scale(mTransfomMatrix, scaleVector);
}
