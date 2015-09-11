#include "BWTriangle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "glm/ext.hpp"

BWTriangle::BWTriangle()
{
	name = std::string("Triangle") + BWCommon::intToString(BWScene::getEntityCount());
	mType = eTriangle;
	mShader = new BWShader("vert.vert", "frag.frag");
}

BWTriangle::~BWTriangle()
{

}

void BWTriangle::Init()
{
	GLfloat vetexData[9] = {
					1.0f , 0.0f , -5.0f,
				   	-1.0f, 0.2f, -5.0f, 
				    0.0f, 2.0f, -5.0f
				   };

	GLfloat vertexColor[9] = {
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f
	};
	
	GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), (void*)vetexData, GL_STATIC_DRAW);
	mShader->registerAttribute("Position", 3, GL_FLOAT, GL_FALSE, 0, 0, 0);

	GLuint vbocolor;
	glGenBuffers(1, &vbocolor);
	glBindBuffer(GL_ARRAY_BUFFER, vbocolor);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), (void*)vertexColor, GL_STATIC_DRAW);	
	mShader->registerAttribute("Color", 3, GL_FLOAT, GL_FALSE, 0, 0, 1);


	if(BWCamera::getCurrentCamera() != 0)
	{
		glm::mat4 viewMatrix = BWCamera::getCurrentCamera()->getMatrix();
		mShader->registerAttributeMatrix4("viewMat", 4, GL_FLOAT, GL_FALSE, 0, viewMatrix, 2);	
	}
	
	mShader->Link();
	mShader->Use();

	if (BWScene::getCurrentScene() != 0)
	{
		glm::mat4 projection = BWScene::getCurrentScene()->getPerspectiveMatrix();	
		BWCommon::DebugOutputMatrix(projection);
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
	}
}

void BWTriangle::Frame()
{
	mShader->Use();
	if(BWCamera::getCurrentCamera() != 0)
	{
		glm::mat4 viewMatrix = BWCamera::getCurrentCamera()->getMatrix();
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	}
	glDrawArrays(GL_TRIANGLES, 0, 3);
}