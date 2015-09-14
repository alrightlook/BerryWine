#include "BWCamera.h"
#include "BWCommon.h"
#include <iostream>
#include "BWKeyEvent.h"
#include "BWMouseEvent.h"

int BWCamera::mIndex = 0;
BWCamera* BWCamera::mpCurrentCamera = 0;

BWCamera::BWCamera()
{
	mIndex++;
	mPostion = glm::vec3(0.0f, 0.0f, 0.15f);
	mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	mUpper = glm::vec3(0.0f, 1.0f, 0.0f);
	mDirection = glm::normalize(mTarget - mPostion);
	mRight = glm::normalize(glm::cross(mDirection, mUpper));
	mLookAtMatrix = glm::lookAt(mPostion, mTarget, mUpper);
	mpCurrentCamera = this;

	mXOffset = 0;
	mYOffset = 0;
	using namespace std::placeholders;
	BWKeyEvent::getInstance()->RegisterListener(std::bind(&BWCamera::KeyEvent, this, _1));
	BWMouseEvent::getInstance()->RegisterEvent(std::bind(&BWCamera::MouseEvent, this, _1));
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
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_A]) {
		mPostion -= mRight * 0.1f;
		mTarget  -= mRight * 0.1f;
	}
	if(state[SDL_SCANCODE_D]) {
		mPostion += mRight * 0.1f;
		mTarget  += mRight * 0.1f;
	}
	if(state[SDL_SCANCODE_W]) {
		mPostion += mDirection * 0.1f;
		mTarget  += mDirection * 0.1f;
	}
	if(state[SDL_SCANCODE_S]) {
		mPostion -= mDirection * 0.1f;
		mTarget  -= mDirection * 0.1f;
	}
}

void BWCamera::Frame()
{
	mDirection = glm::normalize(mTarget - mPostion);
	mRight = glm::normalize(glm::cross(mDirection, mUpper));
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

void BWCamera::MouseEvent(SDL_Event* event)
{
	if(event->type == SDL_MOUSEMOTION)
	{
		int lastX = mXOffset;
		int lastY = mYOffset;
		if (SDL_GetMouseState(&mXOffset, &mYOffset) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			if (lastX != 0 && lastY != 0)
			{
				std::cout<<"x:" << mXOffset - lastX <<" y:"<<mYOffset - lastY<<std::endl;
			}
		}
	}
}