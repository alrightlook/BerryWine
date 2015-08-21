CC = g++
LDFLAGS = -L./SDL/lib/  -lmingw32 -lSDL2main -lSDL2
CFLAGS = -I./SDL/include/ -I./include/
TARGET = berrywineapp
SRC = ./src/main.cpp \
		./src/BWApplication.cpp \
		./src/BWWindow.cpp
$(TARGET):$(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS)  -o ./bin/$(TARGET)

clean:
	rm -fr bin/*.exe
	rm -fr *.o
