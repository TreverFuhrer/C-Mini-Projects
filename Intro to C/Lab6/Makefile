CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: out

out: main.o func.o
	$(CC) $(CFLAGS) -o out main.o func.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

func.o: func.c
	$(CC) $(CFLAGS) -c func.c -o func.o

clean:
	rm -f out *.o