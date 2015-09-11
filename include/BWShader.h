#ifndef BWSHADER_HEADER
#define BWSHADER_HEADER
#include "GL/glew.h"
#include <string>
#include <map>
#include <GL/gl.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class BWShader
{
public:
	enum ShaderType
	{
		vertexShader,
		fragmentShader
	};

	BWShader(const char* vertexShaderFile, const char* fragmentShaderFile);
	void Compile();
	void Link();
	void Use();
	~BWShader();
	std::string getShaderInfoLog(GLenum type);
	std::string getProgramInfoLog();

	void registerUniform(std::string name, GLsizei count, GLfloat* v);
	GLint getUniform(std::string name);

	void registerAttribute(std::string name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset, GLuint index);
	void registerAttributeMatrix4(std::string name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, glm::mat4 offset, GLuint index);
	void refreshAttributeMatrix4(std::string name, glm::mat4 offset);

	GLint getAttribute(std::string name);

	GLuint getProgramID();

private:
	GLuint mProgramID;
	std::string mVertexShaderSrc;
	std::string mFragmentShaderSrc;

	GLuint mVertexShaderID;
	GLuint mFragmentShaderID;

	std::map<std::string, GLint> mMapUniformVariables;
	std::map<std::string, GLuint> mMapAttributeVariables;
};

#endif