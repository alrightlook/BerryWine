#ifndef BWOBJECT_HEADER
#define BWOBJECT_HEADER

class BWObject
{
public:
	BWObject();
	~BWObject();

	virtual void Frame() = 0;
private:

};

#endif