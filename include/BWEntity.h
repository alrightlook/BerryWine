#ifndef BWENTITY_HEADER
#define BWENTITY_HEADER

#include "BWObject.h"
#include <string>

class BWEntity :public BWObject
{
public:
	BWEntity();
	~BWEntity();

	virtual void Init();
	virtual void Frame();
	int getID();
	std::string name;
private:
	int id;
};

#endif