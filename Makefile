
#Makefile for A2

CC=clang
CFLAGS=-Wall -lcurses -lpthread 
DEBUG=-DNDEBUG

all:main

main: console.o frog.o log.o  gameController.o list.o main.o
	$(CC) $(CFLAGS) $(DEBUG) -o A2 console.o frog.o log.o gameController.o list.o main.o
console.o: console.c
	$(CC) $(DEBUG) -c console.c
main.o: main.c
	$(CC) $(DEBUG) -c main.c
log.o: log.c
	$(CC) $(DEBUG) -c log.c
frog.o: frog.c
	$(CC) $(DEBUG) -c frog.c
gameController.o: gameController.c
	$(CC) $(DEBUG) -c gameController.c	
list.o: list.c
	$(CC) $(DEBUG) -c list.c	

clean:
	rm -rf *.o main
