#ifndef BWSHADER_HEADER
#define BWSHADER_HEADER
#include <string>
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

private:
	GLuint mProgramID;
	std::string mVertexShaderSrc;
	std::string mFragmentShaderSrc;

	GLuint mVertexShaderID;
	GLuint mFragmentShaderID;
};

#endif