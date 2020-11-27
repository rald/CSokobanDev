CC=gcc
FLAGS=-Wall -g
LFLAGS=-lgl2d -lglfw -lXrandr -lX11 -lGL -lGLU -lpthread -lm
INCDIR=-I.
LIBDIR=-L.
OBJS=game.o player.o

game: $(OBJS)
	$(CC) -o game $(OBJS) $(LIBDIR) $(LFLAGS) $(FLAGS) 

game.o: game.c
	$(CC) -c game.c $(INCDIR) $(FLAGS)

player.o: player.c player.h
	$(CC) -c player.c $(INCDIR) $(FLAGS)

.PHONY: clean

clean:
	rm $(OBJS) game
