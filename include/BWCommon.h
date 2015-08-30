#ifndef BWCOMMON_HEADER
#define BWCOMMON_HEADER

#include <string>

class BWCommon
{
public:
	static std::string intToString(int n);
	static std::string readFile(const char* fileName);
};
#endif