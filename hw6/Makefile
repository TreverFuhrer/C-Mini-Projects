CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: mgrep

mgrep: tester.o multigrep.o
	$(CC) $(CFLAGS) -o mgrep tester.o multigrep.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

multigrep.o: multigrep.c
	$(CC) $(CFLAGS) -c multigrep.c -o multigrep.o

clean:
	rm -f mgrep *.o
