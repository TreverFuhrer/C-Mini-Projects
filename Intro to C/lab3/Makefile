CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: out

out: tester.o sort.o
	$(CC) $(CFLAGS) -o out tester.o sort.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c -o sort.o

clean:
	rm -f out *.o