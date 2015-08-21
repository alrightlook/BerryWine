#include <iostream>
#include "BWApplication.h"

int main(int argc, char* argv[])
{
	BWApplication app(new BWWindow("Haha", 100, 100, 640, 480));
	app.run();
	return 0;
}