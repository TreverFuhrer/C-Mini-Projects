
/************************* PROGRAM DESCRIPTION *************************
* Implements a simplified and modified version of the UNIX 'ls | sort' command.
*
* USAGE:
*   ./minils [-a] [-R] path
*   -a  Show hidden files     -R  Recursive listing
*   Must input a valid directory path.
***********************************************************************/

/************** DO NOT MODIFY THIS FILE *********************************
* YOUR SUBMISSION WILL BE COMPILED WITH THE ORIGINAL VERSION.
* ANY CHANGES MAY CAUSE COMPILATION TO FAIL DURING GRADING.
***********************************************************************/


#include "utils.h" 

void usage() {
    fprintf(stderr,
        "Usage: ./minils [-a] [-R] path\n"
        "  -a    Include hidden files\n"
        "  -R    Recursively list subdirectories\n"
        "Must input a valid directory path.\n");
    exit(1);
}

int cmp(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(int argc, char *argv[]) {
    minils(argc, argv);
    return 0;
}