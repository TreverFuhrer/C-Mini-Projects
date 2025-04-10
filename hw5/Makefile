CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: minils

minils: tester.o minils.o
	$(CC) $(CFLAGS) -o minils tester.o minils.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

minils.o: minils.c
	$(CC) $(CFLAGS) -c minils.c -o minils.o

clean:
	rm -f minils *.o
