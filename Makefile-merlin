CC=g++
CFLAGS= -g -Wall -std=c++14
EXTERN_LIBRARY=-lopencv_core -lopencv_imgproc -lopencv_highgui
TARGET=zpo
SOURCE=source/*.cpp source/thresholding/*.cpp

all: build clean

build:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(EXTERN_LIBRARY)

clean:
	rm -rf *.o
