#ifndef BWSCENE_HEADER
#define BWSCENE_HEADER

#include "BWObject.h"
#include "BWEntity.h"
#include <map>
#include <string>

class BWScene : public BWObject
{
public:
	BWScene();
	~BWScene();

	void addEntity(BWEntity* entity);
	virtual void Init();
	virtual void Frame();
	static int getEntityCount();
private:
	std::map<int, BWEntity*> mMapEntities;
	static int mEntityCount;
};
#endif