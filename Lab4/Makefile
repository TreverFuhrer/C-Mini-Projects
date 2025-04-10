CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: out

out: tester.o arrays.o
	$(CC) $(CFLAGS) -o out tester.o arrays.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

arrays.o: arrays.c
	$(CC) $(CFLAGS) -c arrays.c -o arrays.o

clean:
	rm -f out *.o