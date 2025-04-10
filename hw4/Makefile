CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: mygrep

mygrep: tester.o grep.o
	$(CC) $(CFLAGS) -o mygrep tester.o grep.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

grep.o: grep.c
	$(CC) $(CFLAGS) -c grep.c -o grep.o

clean:
	rm -f mygrep *.o