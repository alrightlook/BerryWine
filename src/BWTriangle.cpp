#include "BWTriangle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "glm/ext.hpp"

BWTriangle::BWTriangle()
{
	//BWEntity::BWEntity();
	name = std::string("Triangle") + BWCommon::intToString(BWScene::getEntityCount());
	mType = eTriangle;
	mShader = new BWShader("vert.vert", "frag.frag");
	mBufferSize = 12;
}

BWTriangle::~BWTriangle()
{
	if (mShader != 0)
	{
		delete mShader;
		mShader = 0;
	}
}

void BWTriangle::Init()
{
	glBindVertexArray(mVao);
	GLfloat vetexData[12] = {
					1.0f , 0.0f , -5.0f, 1.0f,
				   	-1.0f, 0.0f, -5.0f, 1.0f,
				    0.0f, 2.0f, -5.0f, 1.0f
				   };

	GLfloat vertexColor[9] = {
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 1.0f
	};
	GLuint indices[3] = {0, 1, 2};

	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	RegisterVertexData((void*)vetexData);
	mShader->registerAttribute("Position", 4, GL_FLOAT, GL_FALSE, 0, 0, 0);

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
	
	//We do some transformation test to the triangle here;
	//mTransform.Translate(glm::vec3(0.0f, 0.0f, -5.0f));	 doeable!
	mTransform.Scale(glm::vec3(2.0f, 2.0f, 2.0f));


	if (BWScene::getCurrentScene() != 0)
	{
		glm::mat4 projection = BWScene::getCurrentScene()->getPerspectiveMatrix();	
		BWCommon::DebugOutputMatrix(projection);
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
	}
	mShader->Unuse();
	glBindVertexArray(0);
}

void BWTriangle::Frame()
{
	glBindVertexArray(mVao);
	mShader->EnableAttributes();
	mShader->Use();
	BWEntity::Frame();
	if(BWCamera::getCurrentCamera() != 0)
	{
		glm::mat4 viewMatrix = BWCamera::getCurrentCamera()->getMatrix();
		glUniformMatrix4fv(glGetUniformLocation(mShader->getProgramID(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	}
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	mShader->Unuse();
	glBindVertexArray(0);
}