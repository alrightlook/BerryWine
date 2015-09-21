#ifndef BW_TRIANGE_HEADER
#define BW_TRIANGE_HEADER
#include "BWEntity.h"
#include "BWShader.h"
#include "BWCommon.h"
#include "BWScene.h"
#include "glm/glm.hpp"

#include "BWCommonDef.h"

class BW_DLL BWTriangle : public BWEntity
{
public:
	BWTriangle();
	~BWTriangle();
	virtual void Init();
	virtual void Frame();
private:
	GLfloat* mVertexData;
};
#endif