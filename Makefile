run:
	g++ src/*.cpp -Iinclude -Wall -Wextra -pedantic -lsfml-graphics -lsfml-system -lsfml-window -lGL -lGLEW
	./a.out