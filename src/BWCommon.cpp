#include "BWCommon.h"
#include <sstream>
#include "SDL2/SDL.h"
std::string BWCommon::intToString(int n)
{
	std::stringstream ss;
    ss << n;
    return ss.str();
}