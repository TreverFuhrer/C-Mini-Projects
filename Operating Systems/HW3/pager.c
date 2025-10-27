/*********************************************************************
* Trever Fuhrer, Oct 2025
* Virtual Memory Simulator
**********************************************************************/
#include "utils.h"

#define POLICY_FIFO 0
#define POLICY_LRU 1

typedef struct {
    int page;
    int load_seq;
    int last_seq;
    int occupied;
} Frame;

static Frame frames[256];
static int g_frame_count = 0;

static int seq_counter = 0;
static int total_accesses = 0;
static int page_faults = 0;
static int pages_swapped = 0;

/**
 * Parses a single line from the trace file to extract the hexadecimal address.
 * @param line the input line read from the trace file
 * @param addr pointer to store the parsed address value
 * @return 1 if successfully parsed, 0 otherwise
 */
static int parse_trace_line(const char *line, int *addr) {
    char op = 0;
    int tmp = 0;
    if (sscanf(line, " %c %x", &op, &tmp) == 2) {
        *addr = tmp;
        return 1;
    }
    return 0;
}

/**
 * Converts a virtual memory address to its corresponding page number.
 * @param addr the virtual memory address
 * @return the page number obtained by dividing the address by PAGE_SIZE
 */
static int page_num_from_addr(int addr) {
    return (int)(addr / PAGE_SIZE);
}

/**
 * Searches all currently loaded frames to determine whether the given page
 * is already present in physical memory.
 * @param page the page number being accessed
 * @param frame_count the total number of available frames
 * @return index of the frame if found, or -1 if the page is not resident
 */
static int find_frame(int page, int frame_count) {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i].occupied && frames[i].page == page) {
            return i;
        }
    }
    return -1;
}

/**
 * Selects a victim frame for replacement based on the active policy.
 * - FIFO: chooses the frame with the smallest load sequence number.
 * - LRU: chooses the frame with the smallest last access sequence number.
 * @param policy either POLICY_FIFO or POLICY_LRU
 * @param frame_count total number of physical frames
 * @return index of the victim frame to evict
 */
static int choose_victim(int policy, int frame_count) {
    int best = -1;
    int best_key = 0;
    for (int i = 0; i < frame_count; i++) {
        if (!frames[i].occupied) continue;
        int key = (policy == POLICY_FIFO) ? frames[i].load_seq : frames[i].last_seq;
        if (best == -1 || key < best_key) {
            best = i;
            best_key = key;
        }
    }
    if (best == -1) best = 0;
    return best;
}

/**
 * Prints the final simulation statistics.
 * @param total total number of memory accesses processed
 * @param faults total number of page faults that occurred
 * @param swapped total number of pages evicted (swapped out)
 */
static void print_stats(int total, int faults, int swapped) {
    printf("Total Accesses: %d\n", total);
    printf("Page Faults: %d\n", faults);
    printf("Page Swapped: %d\n", swapped);
}

/**
 * Core simulation loop shared by FIFO and LRU.
 * Tracks total accesses, page faults, and swaps (evictions when full).
 * @param filename trace file
 * @param frame_count number of frames
 * @param policy POLICY_FIFO or POLICY_LRU
 */
static void run_simulation(const char *filename, int frame_count, int policy) {
    g_frame_count = frame_count;
    seq_counter = 0;
    total_accesses = 0;
    page_faults = 0;
    pages_swapped = 0;

    for (int i = 0; i < 256; i++) {
        frames[i].page = 0;
        frames[i].load_seq = 0;
        frames[i].last_seq = 0;
        frames[i].occupied = 0;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open trace file: %s\n", filename);
        return;
    }

    char buf[MAX_LINE];
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        int addr = 0;
        if (!parse_trace_line(buf, &addr)) continue;

        total_accesses++;

        int page = page_num_from_addr(addr);
        int idx = find_frame(page, g_frame_count);

        if (idx != -1) {
            if (policy == POLICY_LRU) frames[idx].last_seq = ++seq_counter;
            continue;
        }

        page_faults++;

        int placed = 0;
        for (int i = 0; i < g_frame_count; i++) {
            if (!frames[i].occupied) {
                frames[i].occupied = 1;
                frames[i].page = page;
                frames[i].load_seq = ++seq_counter;
                frames[i].last_seq = frames[i].load_seq;
                placed = 1;
                break;
            }
        }
        if (placed) continue;

        int victim = choose_victim(policy, g_frame_count);
        pages_swapped++;

        frames[victim].page = page;
        frames[victim].load_seq = ++seq_counter;
        frames[victim].last_seq = frames[victim].load_seq;
    }

    fclose(fp);
    print_stats(total_accesses, page_faults, pages_swapped);
}

/**
 * Runs the FIFO page replacement simulation.
 * @param filename path to trace file
 * @param frame_count number of physical frames
 */
void fifo(char *filename, int frame_count) {
    run_simulation(filename, frame_count, POLICY_FIFO);
}

/**
 * Runs the LRU page replacement simulation.
 * @param filename path to trace file
 * @param frame_count number of physical frames
 */
void lru(char *filename, int frame_count) {
    run_simulation(filename, frame_count, POLICY_LRU);
}