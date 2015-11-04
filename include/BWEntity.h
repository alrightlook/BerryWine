#ifndef BWENTITY_HEADER
#define BWENTITY_HEADER

#include "BWObject.h"
#include <string>
#include "BWShader.h"

#include "BWCommonDef.h"
#include "BWTransform.h"

#include "BWTransform.h"
#include <vector>

enum BWEntityType
{
	eEntity = 0,
	eTriangle = 1,
	eMesh = 2,
	eLight = 3,
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

	GLuint getVao();
	GLuint getIBO();

	GLuint RegisterVertexData(void* data);
	GLuint RegisterVertexData(std::vector<float> data);
protected:
	BWShader* mShader;
	BWEntityType mType;
	int mBufferSize;
	BWTransform mTransform;
	GLuint mVao;
	GLuint mIBO;
private:
	int id;
	
};

#endif