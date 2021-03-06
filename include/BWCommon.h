#ifndef BWCOMMON_HEADER
#define BWCOMMON_HEADER

#include <string>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define PI 3.1415926f

class BWCommon
{
public:
	static std::string intToString(int n);
	static std::string readFile(const char* fileName);
	static void DebugOutputMatrix(glm::mat4 mat);
};
#endif