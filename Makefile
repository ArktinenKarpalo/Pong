CC=g++
CFLAGS=-Wall -std=c++11 -O2 -lGL -I /usr/local/include -I include/ -lXinerama -lXcursor -lXxf86vm -lXrandr -lpthread -ldl -lX11 -lglfw3
LDFLAGS=
SOURCES=$(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
EXECUTABLE=$(SOURCES:.cpp=)

all: $(SOURCES)
	mkdir -p build
	$(CC) $(SOURCES) include/glad/glad.c $(CFLAGS) -o build/koodi
	cp -r src/graphics/shaders build/
clean:
	rm -r build/
