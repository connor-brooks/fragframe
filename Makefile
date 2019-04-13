CC=gcc

all: fragframe

CFLAGS=-g3
LIBS=-lGL -lm -lglfw -lGLEW


fragframe: main.o
	$(CC) $(CFLAGS) $(LIBS) main.o -o fragframe

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o
	rm fragframe
