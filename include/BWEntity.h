#ifndef BWENTITY_HEADER
#define BWENTITY_HEADER

#include "BWObject.h"
#include <string>
#include "BWShader.h"

enum BWEntityType
{
	eEntity = 0,
	eTriangle = 1,
};

class BWEntity :public BWObject
{
public:
	BWEntity();
	~BWEntity();

	virtual void Init();
	virtual void Frame();
	int getID();

	std::string name;
protected:
	BWShader* mShader;
	BWEntityType mType;
private:
	int id;
};

#endif