#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128
#define PAGE_SIZE 4096 

void fifo(char *filename, int frame_count);
void lru(char *filename, int frame_count);
void usage(char *str); // already implemented in tester.c

#endif