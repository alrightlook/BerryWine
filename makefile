CC = g++
LDFLAGS = -L./SDL/lib/ -L./lib/ -lmingw32 -lglew32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -std=c++11
CFLAGS = -I./SDL/include/ -I./include/
TARGET = berrywineapp
SRC = ./src/main.cpp \
		./src/BWApplication.cpp \
		./src/BWWindow.cpp	    \
		./src/BWObject.cpp      \
		./src/BWTimer.cpp		\
		./src/BWScene.cpp		\
		./src/BWEntity.cpp		\
		./src/BWCommon.cpp		\
		./src/BWShader.cpp		\
		./src/BWTriangle.cpp
$(TARGET):$(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS)  -o ./bin/$(TARGET)

clean:
	rm -fr bin/*.exe
	rm -fr *.o
