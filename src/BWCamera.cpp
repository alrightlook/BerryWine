#include "BWCamera.h"

int BWCamera::mIndex = 0;
BWCamera* BWCamera::mpCurrentCamera = 0;

BWCamera::BWCamera()
{
	mIndex++;
	mLookAtMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.15f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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