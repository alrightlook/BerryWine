#ifndef BWSHADER_HEADER
#define BWSHADER_HEADER
#include <string>
#include <map>
#include <GL/gl.h>

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

	void registerAttribute(std::string name, GLint size, GLenum type, GLboolean normalized,GLsizei stride, const void* offset, GLuint index);
	GLint getAttribute(std::string name);

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