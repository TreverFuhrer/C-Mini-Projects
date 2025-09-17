

/************** DO NOT MODIFY THIS FILE *********************************
* YOUR SUBMISSION WILL BE COMPILED WITH THE ORIGINAL VERSION.
* ANY CHANGES MAY CAUSE COMPILATION TO FAIL DURING GRADING.
***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define MAX_FILEPATHS 8192
#define MAX_NAME_LEN 1024

void minils(int argc, char *argv[]);
int cmp(const void *a, const void *b); // already implemeted in the tester.c file
void usage(); // already implemeted in the tester.c file