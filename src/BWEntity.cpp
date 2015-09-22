#include "BWEntity.h"
#include "BWScene.h"
#include "BWCommon.h"
#include "SDL2/SDL.h"
#include "GL/gl.h"

BWEntity::BWEntity()
{
	name = std::string("Entity") + BWCommon::intToString(BWScene::getEntityCount());
	mType = eEntity;
	BWScene::getCurrentScene()->addEntity(this);
}

BWEntity::~BWEntity()
{
	
}

void BWEntity::Init()
{

}

void BWEntity::Frame()
{
	glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "modelMatrix"), 1, GL_FALSE, glm::value_ptr(mTransform.Transform()));
}

 void BWEntity::RegisterVertexData(void* data)
 {
	GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), (void*)data, GL_STATIC_DRAW);
	mShader->registerAttribute("Position", 3, GL_FLOAT, GL_FALSE, 0, 0, 0);
 }


int BWEntity::getID()
{
	return id;
}