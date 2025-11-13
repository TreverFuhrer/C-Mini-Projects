/*********************************************************************
* Trever Fuhrer, Nov 2025
* Multi-Threaded File Search
**********************************************************************/
#include "utils.h"

#define MAX_FILES 5 // Maximum number of files provided through command line arguments
#define MAX_LINE_LENGTH 256 // Maximum number of characters per line when reading from a file
#define MAX_BUFFER_SIZE 2  // Size of the shared circular buffer 

int printUsage();
void runSearch(int argc, char *argv[]);
void *scanFile(void *arg);
void *report();