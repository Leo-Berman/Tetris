tetris.exe: main.cpp
	g++ main.cpp -o tetris.exe -lSDL -lncurses -Wall -Wextra -pedantic
