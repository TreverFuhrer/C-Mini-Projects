CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: out

out: tester.o quest.o
	$(CC) $(CFLAGS) -o out tester.o quest.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

quest.o: quest.c
	$(CC) $(CFLAGS) -c quest.c -o quest.o

clean:
	rm -f out *.o


