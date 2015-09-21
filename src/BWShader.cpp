#include "BWShader.h"
#include "BWCommon.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_opengl.h>


BWShader::BWShader(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	mVertexShaderSrc = BWCommon::readFile(vertexShaderFile);
	mFragmentShaderSrc = BWCommon::readFile(fragmentShaderFile);

	mProgramID = glCreateProgram();

	char* vertexCodeSrc = (char *)malloc(sizeof(char) * (mVertexShaderSrc.size() + 1));
	memcpy(vertexCodeSrc, mVertexShaderSrc.c_str(), mVertexShaderSrc.size() + 1);
	char* fregmentShaderSrc = (char *)malloc(sizeof(char) * (mFragmentShaderSrc.size() + 1));
	memcpy(fregmentShaderSrc, mFragmentShaderSrc.c_str(), mFragmentShaderSrc.size() + 1);

	mVertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	mFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(mVertexShaderID, 1, (const GLchar**)&vertexCodeSrc, 0);
    glCompileShader(mVertexShaderID);
    glAttachShader(mProgramID, mVertexShaderID);
    std::cout<<getShaderInfoLog(GL_VERTEX_SHADER)<<std::endl;

    glShaderSource(mFragmentShaderID, 1, (const GLchar**)&fregmentShaderSrc, 0);
    glCompileShader(mFragmentShaderID);
    glAttachShader(mProgramID, mFragmentShaderID);
	std::cout<<getShaderInfoLog(GL_FRAGMENT_SHADER)<<std::endl;

	std::cout<<getProgramInfoLog()<<std::endl;

}

GLuint BWShader::getProgramID()
{
    return mProgramID;
}

std::string BWShader::getShaderInfoLog(GLenum type)
{

	std::string infoLogRes;
    GLuint shaderId = mFragmentShaderID;
    if (type == GL_VERTEX_SHADER) {
        shaderId = mVertexShaderID;
    }

 	int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH,&infologLength);
    
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(shaderId, infologLength, &charsWritten, infoLog);
        //printf("%s\n",infoLog);
        infoLogRes = infoLog;
        free(infoLog);
    }
    
    return infoLogRes;
}

std::string BWShader::getProgramInfoLog()
{
	std::string infoLogRes;
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    
    glGetProgramiv(mProgramID, GL_INFO_LOG_LENGTH,&infologLength);
    
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(mProgramID, infologLength, &charsWritten, infoLog);
        infoLogRes = infoLog;
        free(infoLog);
    }
    return infoLogRes;
}

BWShader::~BWShader()
{
	glUseProgram(0);
	glDetachShader(mProgramID, mFragmentShaderID);
    glDetachShader(mProgramID, mVertexShaderID);
    
    glDeleteShader(mFragmentShaderID);
    glDeleteShader(mVertexShaderID);
    
    glDeleteProgram(mProgramID);
}

void BWShader::Compile()
{

}

void BWShader::registerAttributeMatrix4(std::string name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, glm::mat4 offset, GLuint index)
{
    if (mMapAttributeVariables.find(name) == mMapAttributeVariables.end())
    {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), glm::value_ptr(offset), GL_DYNAMIC_DRAW);

        glBindAttribLocation(mProgramID, index, name.c_str());
        for (int i = 0 ; i < 4; i++)
        {
            glEnableVertexAttribArray(index + i);
            glVertexAttribPointer(index + i, size, type, normalized, stride, (void*)(4 * sizeof(GLfloat) * i));
            glVertexAttribDivisor(index + i, 1);
        }

        mMapAttributeVariables.insert(make_pair(name, index));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void BWShader::registerAttribute(std::string name, GLint size, GLenum type, GLboolean normalized,GLsizei stride, const void* offset, GLuint index)
{
    if (mMapAttributeVariables.find(name) == mMapAttributeVariables.end())
    {
        glBindAttribLocation(mProgramID, index, name.c_str());
        glVertexAttribPointer(index, size, type, normalized, stride, offset);
        glEnableVertexAttribArray(index);
        mMapAttributeVariables.insert(make_pair(name, index));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

GLint BWShader::getAttribute(std::string name)
{
    if (mMapAttributeVariables.find(name) == mMapAttributeVariables.end())
    {
        return mMapAttributeVariables.find(name)->second;
    }
    return 0;
}

void BWShader::registerUniform(std::string name, GLsizei count, GLfloat* v)
{
    if (mMapUniformVariables.find(name) == mMapUniformVariables.end())
    {
        GLint ul = glGetUniformLocation(mProgramID, name.c_str());
        mMapUniformVariables.insert(std::make_pair(name, ul));
        glUniformMatrix4fv(ul, count, GL_FALSE, v);
    }
}

GLint BWShader::getUniform(std::string name)
{
    if(mMapUniformVariables.find(name) != mMapUniformVariables.end())
    {
        return mMapUniformVariables.find(name)->second;
    }
    return 0;
}

void BWShader::Link()
{
	glLinkProgram(mProgramID);
    std::cout<<getProgramInfoLog()<<std::endl;
}

void BWShader::Unuse()
{
	glUseProgram(0);
}

void BWShader::Use()
{
	glUseProgram(mProgramID);
}

void BWShader::refreshAttributeMatrix4(std::string name, glm::mat4 offset)
{
    if (mMapAttributeVariables.find(name) != mMapAttributeVariables.end())
    {
        GLuint vbo = mMapAttributeVariables.find(name)->second;
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER,0, 16 * sizeof(GLfloat), glm::value_ptr(offset));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}