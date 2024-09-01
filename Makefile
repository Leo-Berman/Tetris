tetris.exe: main.cpp
	g++ -c *.cpp -lSDL -lncurses-Wall -Wextra -pedantic
	g++ *.o -o tetris.exe -lSDL -lncurses -Wall -Wextra -pedantic
