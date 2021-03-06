#ifndef BWTIMER_HEADER
#define BWTIMER_HEADER
#include "BWObject.h"
#include "BWCommonDef.h"
class BW_DLL BWTimer : public BWObject
{
public:
	static BWTimer* getInstance();
	long GetFPS();
	void Frame();
	void Init();
private:
	static BWTimer* mInstance;
	BWTimer();
	~BWTimer();

	long mEclapseFrame;
	long mEclapseTime;
	long mLastTime;
	long mLastFrame;
};
#endif