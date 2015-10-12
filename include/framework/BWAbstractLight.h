#ifndef BW_ABSTRACT_LIGHT
#define BW_ABSTRACT_LIGHT
#include "BWEntity.h"

class BWAbstractLight : public BWEntity
{
public:
	BWAbstractLight();
	~BWAbstractLight();

	virtual void Init();
	virtual void Frame();

protected:
	bool mEnable;
private:

};
#endif