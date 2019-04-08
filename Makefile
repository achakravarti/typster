SRC := src/merak/shade.c src/merak/screen.c src/merak/game.c \
       src/merak/area.c src/merak/event.c src/merak/point.c src/typster.c
INC := -I "../"
LIB := ../sol/bld/bin/libsol.so

all:
	gcc $(INC) -Wall -Wextra -o typster $(SRC) -lSDL2 -lm $(LIB)

