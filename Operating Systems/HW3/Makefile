CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: tvm

tvm: tester.o pager.o
	$(CC) $(CFLAGS) -o tvm tester.o pager.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

pager.o: pager.c
	$(CC) $(CFLAGS) -c pager.c -o pager.o

clean:
	rm -f tvm *.o