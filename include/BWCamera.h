#ifndef BW_CAMERA_HEADER
#define BW_CAMERA_HEADER
#include "BWObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"
#include <functional>
#include "SDL2/SDL.h"

class BWCamera :public BWObject
{
public:
	BWCamera();
	~BWCamera();
	static int getIndex();
	virtual void Init();
	virtual void Frame();

	void setPostion(glm::vec3 postion, glm::vec3 target);
	void setPostion(glm::vec3 postion);
	
	glm::mat4 getMatrix();
	static BWCamera* getCurrentCamera();
	void KeyEvent(SDL_Event* event);
	void MouseEvent(SDL_Event* event);


private:
	glm::vec3 mPostion;
	glm::vec3 mTarget;
	glm::vec3 mUpper;
	glm::vec3 mDirection;
	glm::vec3 mRight;

	glm::mat4 mLookAtMatrix;
	static BWCamera* mpCurrentCamera;
	static int mIndex;

	void calculateDirection(int xoffset, int yoffset);
	void spray(int xoffset);
	void pitch(int yoffset);

	int mXOffset;
	int mYOffset;
	float mYawAngle;
	float mPitchAngle;

	int mXLastPos;
	int mYLastPos;

	bool mButtonDown;
	bool bRepaint;

	const float mDeltaAngle;
};
#endif