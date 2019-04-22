SRC := src/merak/screen.c src/merak/game.c src/merak/entity.c \
       src/merak/event.c src/enemy.c src/merak/vector.c \
       src/merak/texture.c src/merak/sprite.c src/typster.c src/merak/keyboard.c
INC := -I "../"
LIB := ../sol/bld/bin/libsol.so

all:
	gcc $(INC) -Wall -Wextra -o typster $(SRC) -lSDL2 -lSDL2_image -lm $(LIB)

