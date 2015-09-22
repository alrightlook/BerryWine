#ifndef BWENTITY_HEADER
#define BWENTITY_HEADER

#include "BWObject.h"
#include <string>
#include "BWShader.h"

#include "BWCommonDef.h"
#include "BWTransform.h"

#include "BWTransform.h"

enum BWEntityType
{
	eEntity = 0,
	eTriangle = 1,
	eMesh = 2,
};

class BW_DLL BWEntity :public BWObject
{
public:
	BWEntity();
	~BWEntity();

	virtual void Init();
	virtual void Frame();
	int getID();

	std::string name;

	virtual void RegisterVertexData(void* data);
protected:
	BWShader* mShader;
	BWEntityType mType;

	BWTransform mTransform;
private:
	int id;
};

#endif