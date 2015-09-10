#include "BWTriangle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

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
					1.0f , 0.0f , -10.0f,
				   	-1.0f, 0.0f, -10.0f, 
				    0.0f, 1.0f, -10.0f
				   };

	GLfloat vertexColor[9] = {
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f
	};


	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.15f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	//BWCommon::DebugOutputMatrix(viewMatrix);

	glm::mat4 projection = glm::perspective(60.0f, 640/480.0f, 0.1f, 150.f);
	//BWCommon::DebugOutputMatrix(projection);

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

	mShader->Link();
	mShader->Use();

	glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));

}

void BWTriangle::Frame()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}