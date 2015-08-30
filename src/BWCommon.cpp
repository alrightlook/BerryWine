#include "BWCommon.h"
#include <sstream>
#include "SDL2/SDL.h"
#include <fstream>
#include <iostream>

using namespace std;

std::string BWCommon::intToString(int n)
{
	stringstream ss;
    ss << n;
    return ss.str();
}


std::string BWCommon::readFile(const char* fileName)
{
	string line;
	string fileContent;
	ifstream srcFile(fileName);
	if (srcFile.is_open())
	{
		while ( getline (srcFile,line) )
		{
			fileContent += line + "\n";
		}
		srcFile.close();
	}
	return fileContent;
}