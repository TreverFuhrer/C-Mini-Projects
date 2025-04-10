CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: out

out: tester.o cr.o
	$(CC) $(CFLAGS) -o out tester.o cr.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

cr.o: cryptic.c
	$(CC) $(CFLAGS) -c cryptic.c -o cr.o

clean:
	rm -f out *.o
