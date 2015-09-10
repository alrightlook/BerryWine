#include "BWCamera.h"

int BWCamera::mIndex = 0;
BWCamera* BWCamera::mpCurrentCamera = 0;

BWCamera::BWCamera()
{
	mIndex++;
	mPostion = glm::vec3(0.0f, 0.0f, 0.15f);
	mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	mLookAtMatrix = glm::lookAt(mPostion, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));
	mpCurrentCamera = this;
}

int BWCamera::getIndex()
{
	return mIndex;
}

BWCamera::~BWCamera()
{

}

void BWCamera::Init()
{

}

void BWCamera::Frame()
{
	mPostion[0] += 0.1f;
	mLookAtMatrix = glm::lookAt(mPostion, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 BWCamera::getMatrix()
{
	return mLookAtMatrix;
}

BWCamera* BWCamera::getCurrentCamera()
{
	return mpCurrentCamera;
}


void BWCamera::setPostion(glm::vec3 postion, glm::vec3 target)
{
	mPostion = postion;
	mTarget = target;
}

void BWCamera::setPostion(glm::vec3 postion)
{
	mPostion = postion;
}