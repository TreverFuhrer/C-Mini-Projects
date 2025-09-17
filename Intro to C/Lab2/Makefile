CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: out

out: main.o sum.o
	$(CC) $(CFLAGS) -o out main.o sum.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

add.o: add.c
	$(CC) $(CFLAGS) -c sum.c
	
clean:
	rm -f out *.o