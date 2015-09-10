#ifndef BWSCENE_HEADER
#define BWSCENE_HEADER

#include "BWObject.h"
#include "BWEntity.h"
#include <map>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class BWScene : public BWObject
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
private:
	static BWScene* mpCurrentScene;
	glm::mat4 mPerspectiveMatrix;
	std::map<int, BWEntity*> mMapEntities;
	static int mEntityCount;
};
#endif