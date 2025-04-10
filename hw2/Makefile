CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: mystack

mystack: tester.o stk.o
	$(CC) $(CFLAGS) -o mystack tester.o stk.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

stk.o: stack.c
	$(CC) $(CFLAGS) -c stack.c -o stk.o

clean:
	rm -f mystack *.o
