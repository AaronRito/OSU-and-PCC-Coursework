CFLAGS = -g -Wall -fpic -lm -std=c99

default: all

all: rito_server.o
	gcc main.c rito_server.o -o rito_server $(CFLAGS)
	
clean:
	rm -f rito_server.o rito_server

rito_server.o: rito_server.c
	gcc -c rito_server.c -o rito_server.o $(CFLAGS)
