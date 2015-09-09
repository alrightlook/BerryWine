#include "BWTriangle.h"

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
					1.0f , 0.0f , 0.0f,
				   	-1.0f, 0.0f, 0.0f, 
				    0.0f, 1.0f, 0.0f
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

	mShader->Link();
	mShader->Use();
}

void BWTriangle::Frame()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}