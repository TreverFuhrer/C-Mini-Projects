/*******************************************************************

* Description: 
* This C program implements modified versions of the 'grep' command commonly found in Unix-like operating systems. 
* The 'grep' command is used to search for specific patterns within text files.

Usage:
* Compile it using a C compiler and run the executable from the command line with appropriate arguments.
*    - ./mygrep <pattern> <file> [-i] [-n]
*    - optional arguments are specified in [ ]
*******************************************************************/


#include "text.h"

void usage() {
    fprintf(stderr, "Usage: ./mygrep <pattern> <filename> with optional [-i] for case insensitive search, [-n] for line number\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    
    grepLite(argc, argv);
 
    return 0;
}