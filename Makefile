SRC := src/marek/shade.c src/marek/screen.c src/typster.c
INC := -I "../"
LIB := ../sol/bld/bin/libsol.so

all:
	gcc $(INC) -Wall -Wextra -o typster $(SRC) -lSDL2 -lm $(LIB)

