#ifndef BWSCENE_HEADER
#define BWSCENE_HEADER

#include "BWObject.h"
#include "BWEntity.h"
#include <map>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "BWCamera.h"
#include "BWCommonDef.h"

class BW_DLL BWScene : public BWObject
{
public:
	BWScene();
	~BWScene();

	void addEntity(BWEntity* entity);
	virtual void Init();
	virtual void Frame();
	static int getEntityCount();
	glm::mat4 getPerspectiveMatrix();
	static BWScene* getCurrentScene();
	void addCamera(BWCamera* camera);
private:
	static BWScene* mpCurrentScene;
	glm::mat4 mPerspectiveMatrix;
	std::map<int, BWEntity*> mMapEntities;
	std::map<int, BWCamera*> mMapCameras;
	static int mEntityCount;
};
#endif