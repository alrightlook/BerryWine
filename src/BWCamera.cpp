#include "BWCamera.h"
#include "BWCommon.h"
#include <iostream>
#include "BWKeyEvent.h"

int BWCamera::mIndex = 0;
BWCamera* BWCamera::mpCurrentCamera = 0;

BWCamera::BWCamera()
{
	mIndex++;
	mPostion = glm::vec3(0.0f, 0.0f, 0.15f);
	mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	mLookAtMatrix = glm::lookAt(mPostion, mTarget, glm::vec3(0.0f, 1.0f, 0.0f));
	mpCurrentCamera = this;

	using namespace std::placeholders;
	BWKeyEvent::getInstance()->RegisterListener(std::bind(&BWCamera::KeyEvent, this, _1));
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

void BWCamera::KeyEvent(SDL_Event* event)
{
	switch(event->key.keysym.sym)
	{
		case SDLK_a:
		{
			mPostion[0] -= 0.1f;
			mTarget[0] -= 0.1f;
			break;
		}
		case SDLK_d:
		{
			mPostion[0] += 0.1f;
			mTarget[0] += 0.1f;
			break;
		}
		case SDLK_w:
		{
			mPostion[2] -= 0.1f;
			mTarget[2] -= 0.1f;
			break;
		}
		case SDLK_s:
		{
			mPostion[2] += 0.1f;
			mTarget[2] += 0.1f;
			break;
		}

	}
}

void BWCamera::Frame()
{
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