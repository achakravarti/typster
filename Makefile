SRC := src/marek/shade.c src/marek/screen.c src/typster.c

all:
	gcc -Wall -Wextra -o typster $(SRC) -lSDL2 -lm

