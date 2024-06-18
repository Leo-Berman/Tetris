tetris.exe: main.cpp
	g++ -c *.cpp -Wall -Wextra -pedantic
	g++ *.o -o tetris.exe -Wall -Wextra -pedantic
clean:
	rm *.o *.exe
