#include "BWEntity.h"
#include "BWScene.h"
#include "BWCommon.h"
#include "SDL2/SDL.h"
#include "GL/gl.h"
#include <vector>

#include <iostream>

BWEntity::BWEntity()
{
	name = std::string("Entity") + BWCommon::intToString(BWScene::getEntityCount());
	mType = eEntity;
	BWScene::getCurrentScene()->addEntity(this);
	mBufferSize = 0;
	glGenVertexArrays(1, &mVao);
}

GLuint BWEntity::getIBO()
{
	return mIBO;
}

BWEntity::~BWEntity()
{
	
}

void BWEntity::Init()
{

}

GLuint BWEntity::getVao()
{
	return mVao;
}

void BWEntity::Frame()
{
	glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(mTransform.Transform()));
}

 GLuint BWEntity::RegisterVertexData(void* data)
 {
	GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mBufferSize * sizeof(GLfloat), (void*)data, GL_STATIC_DRAW);
	return vbo;

 }
 GLuint BWEntity::RegisterVertexData(std::vector<float> data)
 {
	GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), (void*)&data[0], GL_STATIC_DRAW);
	return vbo;
 }


int BWEntity::getID()
{
	return id;
}