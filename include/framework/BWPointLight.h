#ifndef BWPOINT_LIGHT_HEADER
#define BWPOINT_LIGHT_HEADER
#include "BWCommonDef.h"
#include "BWAbstractLight.h"

class BW_DLL BWPointLight : public BWAbstractLight
{
public:
	BWPointLight();
	~BWPointLight();

	void Init();
	void Frame();
private:
	
};
#endif