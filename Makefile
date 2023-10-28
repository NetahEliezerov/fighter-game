all:
	g++ -std=c++17 -I libraries/include -L libraries/lib -o main src/main.cpp src/utils/*.cpp src/movement/*.cpp -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2
