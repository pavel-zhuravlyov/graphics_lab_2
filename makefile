CC=g++
CFLAGS=-lSDL2 -lGLEW -lGL -std=c++11


all:  
	$(CC) main.cpp display.cpp shader.cpp stb_image.c texture.cpp mesh.cpp $(CFLAGS) -o main -g

