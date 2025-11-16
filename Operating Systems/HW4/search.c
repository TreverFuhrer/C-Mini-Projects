/*********************************************************************
* Trever Fuhrer, Nov 2025
* Multi-Threaded File Search
**********************************************************************/
#include "utils.h"

typedef struct {
    char *filename;
    char *pattern;
    int count;
} Result;

typedef struct {
    char *filename;
    char *pattern;
} ScanArgs;

Result buffer[MAX_BUFFER_SIZE];
int buf_in = 0;
int buf_out = 0;
int buf_cnt = 0;

pthread_mutex_t buf_mutex;
pthread_cond_t buf_not_full;
pthread_cond_t buf_not_empty;

int total_files = 0;
int printed_results = 0;
char *pattern = NULL;

/*  
 * Runs the multi-threaded search simulation.
 * @param argc number of command line arguments
 * @param argv array of command line argument strings
 */
void runSearch(int argc, char *argv[]) {
    if (argc < 4) {
        printUsage();
        return;
    }

    pattern = argv[1];

    size_t pat_len = strlen(pattern);
    if (pat_len < 3 || pat_len > 10) {
        printUsage();
        return;
    }

    if (strcmp(argv[2], "-f") != 0) {
        printUsage();
        return;
    }

    total_files = argc - 3;
    if (total_files < 2 || total_files > MAX_FILES) {
        printUsage();
        return;
    }

    buf_in = 0;
    buf_out = 0;
    buf_cnt = 0;
    printed_results = 0;

    pthread_mutex_init(&buf_mutex, NULL);
    pthread_cond_init(&buf_not_full, NULL);
    pthread_cond_init(&buf_not_empty, NULL);

    ScanArgs args[total_files];
    pthread_t scanner_threads[total_files];
    pthread_t reporter_thread;

    for (int i = 0; i < total_files; i++) {
        args[i].filename = argv[3 + i];
        args[i].pattern = pattern;
    }

    pthread_create(&reporter_thread, NULL, report, NULL);

    for (int i = 0; i < total_files; i++) {
        pthread_create(&scanner_threads[i], NULL, scanFile, &args[i]);
    }

    for (int i = 0; i < total_files; i++) {
        pthread_join(scanner_threads[i], NULL);
    }

    pthread_join(reporter_thread, NULL);

    pthread_mutex_destroy(&buf_mutex);
    pthread_cond_destroy(&buf_not_full);
    pthread_cond_destroy(&buf_not_empty);
}

/*  
 * Scans a file for occurrences of a pattern and stores the result in the buffer.
 * @param arg pointer to ScanArgs structure containing filename and pattern
 */
void *scanFile(void *arg) {
    ScanArgs *sa = (ScanArgs *) arg;
    char *file = sa->filename;
    char *pat = sa->pattern;

    int count = 0;
    FILE *fp = fopen(file, "r");

    if (fp != NULL) {
        char line[MAX_LINE_LENGTH * 5];
        int in_line_has_match = 0;

        while (fgets(line, sizeof(line), fp) != NULL) {
            if (!in_line_has_match && strstr(line, pat) != NULL) {
                in_line_has_match = 1;
            }

            if (strchr(line, '\n') != NULL) {
                if (in_line_has_match) {
                    count++;
                }
                in_line_has_match = 0;
            }
        }

        if (in_line_has_match) {
            count++;
        }

        fclose(fp);
    }
    else {
        count = 0;
    }

    pthread_mutex_lock(&buf_mutex);

    while (buf_cnt == MAX_BUFFER_SIZE) {
        pthread_cond_wait(&buf_not_full, &buf_mutex);
    }

    buffer[buf_in].filename = file;
    buffer[buf_in].pattern = pat;
    buffer[buf_in].count = count;

    buf_in = (buf_in + 1) % MAX_BUFFER_SIZE;
    buf_cnt++;

    pthread_cond_signal(&buf_not_empty);
    pthread_mutex_unlock(&buf_mutex);

    return NULL;
}

/*  
 * Reports results from the buffer until all results have been printed.
 * @return NULL
 */
void *report() {
    while (1) {
        pthread_mutex_lock(&buf_mutex);

        while (buf_cnt == 0 && printed_results < total_files) {
            pthread_cond_wait(&buf_not_empty, &buf_mutex);
        }

        if (buf_cnt == 0 && printed_results == total_files) {
            pthread_mutex_unlock(&buf_mutex);
            break;
        }

        Result r = buffer[buf_out];
        buf_out = (buf_out + 1) % MAX_BUFFER_SIZE;
        buf_cnt--;
        printed_results++;

        pthread_cond_signal(&buf_not_full);
        pthread_mutex_unlock(&buf_mutex);

        printf("Pattern %s found %d times in file %s\n", r.pattern, r.count, r.filename);
    }
    return NULL;
}
