CC=gcc

all: fragframe

CFLAGS=-g3
LIBS=-lGL -lm -lglfw -lGLEW

fragframe: main.o
	$(CC) $(CFLAGS) main.o -o _fragframe $(LIBS) 

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o
	rm _fragframe
