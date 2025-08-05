CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -O2 `sdl2-config --cflags` -Iinclude
LDFLAGS=`sdl2-config --libs` -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lSDL2
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

BIN=bin/pacman

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)
