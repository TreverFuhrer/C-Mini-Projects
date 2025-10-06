/*********************************************************************
* Author: Trever J. Fuhrer, September 2025
* sim: simple simulator for scheduling algorithms.
**********************************************************************/
#include "utils.h"

/**
 * Description:
 *  - Runs the First-Come-First-Serve (FCFS) scheduling algorithm.
 *
 * Parameters:
 *  - argc: Argument count from command line.
 *  - argv: Argument vector from command line.
 */
void run_fcfs(int argc, char *argv[]) {
    if (argc < 3) {
        usage("Error: Missing input file for FCFS.");
        return;
    }

    const char *input_file = argv[2];
    Process processes[MAX_PROCESSES];

    /* read file */
    FILE *fp = fopen(input_file, "r");
    if (fp == NULL) {
        usage("Error: Input file not found.");
        return;
    }

    int process_count = 0;
    while (process_count < MAX_PROCESSES) {
        char pid[MAX_NAME_LEN];
        int at;
        int rt;

        int got = fscanf(fp, "%19s %d %d", pid, &at, &rt);
        if (got == EOF) {
            break;
        }
        if (got != 3) {
            fclose(fp);
            fprintf(stderr, "Error: Bad input format.\n");
            exit(EXIT_FAILURE);
        }

        strncpy(processes[process_count].pid, pid, MAX_NAME_LEN - 1);
        processes[process_count].pid[MAX_NAME_LEN - 1] = '\0';
        processes[process_count].arrival_time = at;
        processes[process_count].run_time = rt;
        processes[process_count].remaining_time = rt;
        processes[process_count].initial_schedule_time = -1;
        processes[process_count].completion_time = -1;
        process_count++;
    }
    fclose(fp);

    if (process_count < 2 || process_count > 5) {
        fprintf(stderr, "Error: Number of processes must be between 2 and 5.\n");
        exit(EXIT_FAILURE);
    }

    /* ready queue as simple circular array */
    int ready_queue[MAX_PROCESSES];
    int rq_front = 0;
    int rq_rear = 0;
    int rq_size = 0;

    printf("Running FCFS\n");
    printf("Time | Running  | Ready Queue\n");
    printf("-----------------------------\n");

    int next_index = 0;
    int now = 0;
    int current = -1;
    int finished = 0;
    int context_switches = 0;

    double sum_response = 0.0;
    double sum_turnaround = 0.0;

    /* enqueue any arrivals at time 0 */
    while (next_index < process_count && processes[next_index].arrival_time == 0) {
        if (rq_size < MAX_PROCESSES) {
            ready_queue[rq_rear] = next_index;
            rq_rear = (rq_rear + 1) % MAX_PROCESSES;
            rq_size++;
        }
        next_index++;
    }

    while (finished < process_count) {
        /* idle tick before next arrival (if any) */
        if (current == -1 && rq_size == 0 && next_index < process_count && now < processes[next_index].arrival_time) {
            int start = now;
            int end = now + 1;

            now = end;

            while (next_index < process_count && processes[next_index].arrival_time == now) {
                if (rq_size < MAX_PROCESSES) {
                    ready_queue[rq_rear] = next_index;
                    rq_rear = (rq_rear + 1) % MAX_PROCESSES;
                    rq_size++;
                }
                next_index++;
            }

            if (rq_size == 0) {
                printf("%4d - %-4d | %-8s| -\n", start, end, "IDLE");
            }
            else {
                char line[256];
                line[0] = '\0';
                int idx = rq_front;
                for (int i = 0; i < rq_size; i++) {
                    if (i > 0) {
                        strncat(line, " ", sizeof(line) - strlen(line) - 1);
                    }
                    strncat(line, processes[ready_queue[idx]].pid, sizeof(line) - strlen(line) - 1);
                    idx = (idx + 1) % MAX_PROCESSES;
                }
                printf("%4d - %-4d | %-8s| %s\n", start, end, "IDLE", line);
            }

            continue;
        }

        /* pick a process if CPU free */
        if (current == -1 && rq_size > 0) {
            current = ready_queue[rq_front];
            rq_front = (rq_front + 1) % MAX_PROCESSES;
            rq_size--;

            if (processes[current].initial_schedule_time == -1) {
                processes[current].initial_schedule_time = now;
            }
        }

        int start = now;
        int end = now + 1;

        const char *running_label;
        if (current == -1) {
            running_label = "IDLE";
        }
        else {
            running_label = processes[current].pid;
        }

        if (current != -1) {
            processes[current].remaining_time--;

            if (processes[current].remaining_time == 0) {
                processes[current].completion_time = end;
                finished++;

                if (rq_size == 0 && next_index < process_count) {
                    context_switches++;
                }

                current = -1;
            }
        }

        now = end;

        /* add arrivals that happen exactly at this boundary */
        while (next_index < process_count && processes[next_index].arrival_time == now) {
            if (rq_size < MAX_PROCESSES) {
                ready_queue[rq_rear] = next_index;
                rq_rear = (rq_rear + 1) % MAX_PROCESSES;
                rq_size++;
            }
            next_index++;
        }

        /* print ready queue snapshot at end boundary */
        if (rq_size == 0) {
            printf("%4d - %-4d | %-8s| -\n", start, end, running_label);
        }
        else {
            char line[256];
            line[0] = '\0';
            int idx = rq_front;
            for (int i = 0; i < rq_size; i++) {
                if (i > 0) {
                    strncat(line, " ", sizeof(line) - strlen(line) - 1);
                }
                strncat(line, processes[ready_queue[idx]].pid, sizeof(line) - strlen(line) - 1);
                idx = (idx + 1) % MAX_PROCESSES;
            }
            printf("%4d - %-4d | %-8s| %s\n", start, end, running_label, line);
        }

        /* if we will immediately start another real process, count a switch */
        if (current == -1 && rq_size > 0) {
            current = ready_queue[rq_front];
            rq_front = (rq_front + 1) % MAX_PROCESSES;
            rq_size--;

            context_switches++;

            if (processes[current].initial_schedule_time == -1) {
                processes[current].initial_schedule_time = now;
            }
        }
    }

    for (int i = 0; i < process_count; i++) {
        int resp = processes[i].initial_schedule_time - processes[i].arrival_time;
        int turn = processes[i].completion_time - processes[i].arrival_time;
        sum_response += resp;
        sum_turnaround += turn;
    }

    printf("\nFCFS Execution Completed.\n");
    printf("Average Response Time: %.2f ms\n", sum_response / process_count);
    printf("Average Turnaround Time: %.2f ms\n", sum_turnaround / process_count);
    printf("Total Context Switches: %d\n\n", context_switches);
}

/**
 * Description:
 *  - Runs the Round-Robin (RR) scheduling algorithm.
 *
 * Parameters:
 *  - argc: Argument count from command line.
 *  - argv: Argument vector from command line.
 */
void run_rr(int argc, char *argv[]) {
    if (argc < 4) {
        usage("Error: Missing time slice for RR.");
        return;
    }

    const char *input_file = argv[2];
    int time_slice = atoi(argv[3]);

    if (time_slice < 2 || time_slice > 4) {
        usage("Error: Invalid time slice. Must be 2-4 ms.");
        return;
    }

    Process processes[MAX_PROCESSES];

    /* read file */
    FILE *fp = fopen(input_file, "r");
    if (fp == NULL) {
        usage("Error: Input file not found.");
        return;
    }

    int process_count = 0;
    while (process_count < MAX_PROCESSES) {
        char pid[MAX_NAME_LEN];
        int at;
        int rt;

        int got = fscanf(fp, "%19s %d %d", pid, &at, &rt);
        if (got == EOF) {
            break;
        }
        if (got != 3) {
            fclose(fp);
            fprintf(stderr, "Error: Bad input format.\n");
            exit(EXIT_FAILURE);
        }

        strncpy(processes[process_count].pid, pid, MAX_NAME_LEN - 1);
        processes[process_count].pid[MAX_NAME_LEN - 1] = '\0';
        processes[process_count].arrival_time = at;
        processes[process_count].run_time = rt;
        processes[process_count].remaining_time = rt;
        processes[process_count].initial_schedule_time = -1;
        processes[process_count].completion_time = -1;

        process_count++;
    }
    fclose(fp);

    if (process_count < 2 || process_count > 5) {
        fprintf(stderr, "Error: Number of processes must be between 2 and 5.\n");
        exit(EXIT_FAILURE);
    }

    /* ready queue (circular) */
    int ready_queue[MAX_PROCESSES];
    int rq_front = 0;
    int rq_rear = 0;
    int rq_size = 0;

    printf("Running RR\n");
    printf("Time | Running  | Ready Queue\n");
    printf("-----------------------------\n");

    int next_index = 0;
    int now = 0;
    int current = -1;
    int finished = 0;
    int context_switches = 0;

    double sum_response = 0.0;
    double sum_turnaround = 0.0;

    /* enqueue arrivals at time 0 */
    while (next_index < process_count && processes[next_index].arrival_time == 0) {
        if (rq_size < MAX_PROCESSES) {
            ready_queue[rq_rear] = next_index;
            rq_rear = (rq_rear + 1) % MAX_PROCESSES;
            rq_size++;
        }
        next_index++;
    }

    while (finished < process_count) {
        /* idle 1ms steps until first/next arrival */
        if (current == -1 && rq_size == 0 && next_index < process_count && now < processes[next_index].arrival_time) {
            int start = now;
            int end = now + 1;

            now = end;

            while (next_index < process_count && processes[next_index].arrival_time == now) {
                if (rq_size < MAX_PROCESSES) {
                    ready_queue[rq_rear] = next_index;
                    rq_rear = (rq_rear + 1) % MAX_PROCESSES;
                    rq_size++;
                }
                next_index++;
            }

            if (rq_size == 0) {
                printf("%4d - %-4d | %-8s| -\n", start, end, "IDLE");
            }
            else {
                char line[256];
                line[0] = '\0';
                int idx = rq_front;
                for (int i = 0; i < rq_size; i++) {
                    if (i > 0) {
                        strncat(line, " ", sizeof(line) - strlen(line) - 1);
                    }
                    strncat(line, processes[ready_queue[idx]].pid, sizeof(line) - strlen(line) - 1);
                    idx = (idx + 1) % MAX_PROCESSES;
                }
                printf("%4d - %-4d | %-8s| %s\n", start, end, "IDLE", line);
            }

            continue;
        }

        /* pick a process if CPU free */
        if (current == -1 && rq_size > 0) {
            current = ready_queue[rq_front];
            rq_front = (rq_front + 1) % MAX_PROCESSES;
            rq_size--;

            if (processes[current].initial_schedule_time == -1) {
                processes[current].initial_schedule_time = now;
            }
        }

        if (current == -1) {
            continue;
        }

        int start = now;

        int remaining = processes[current].remaining_time;
        int chunk;
        if (remaining < time_slice) {
            chunk = remaining;
        }
        else {
            chunk = time_slice;
        }

        int end = now + chunk;

        /* run the chunk */
        processes[current].remaining_time -= chunk;

        /* enqueue arrivals in (start, end] BEFORE showing the snapshot */
        while (next_index < process_count && processes[next_index].arrival_time <= end) {
            if (processes[next_index].arrival_time > start) {
                if (rq_size < MAX_PROCESSES) {
                    ready_queue[rq_rear] = next_index;
                    rq_rear = (rq_rear + 1) % MAX_PROCESSES;
                    rq_size++;
                }
            }
            next_index++;
        }

        /* print the queue at END boundary BEFORE putting current back */
        if (rq_size == 0) {
            printf("%4d - %-4d | %-8s| -\n", start, end, processes[current].pid);
        }
        else {
            char line[256];
            line[0] = '\0';
            int idx = rq_front;
            for (int i = 0; i < rq_size; i++) {
                if (i > 0) {
                    strncat(line, " ", sizeof(line) - strlen(line) - 1);
                }
                strncat(line, processes[ready_queue[idx]].pid, sizeof(line) - strlen(line) - 1);
                idx = (idx + 1) % MAX_PROCESSES;
            }
            printf("%4d - %-4d | %-8s| %s\n", start, end, processes[current].pid, line);
        }

        /* complete or preempt AFTER printing (so current isn't shown in same line's queue) */
        if (processes[current].remaining_time == 0) {
            processes[current].completion_time = end;
            finished++;
        }
        else {
            if (rq_size < MAX_PROCESSES) {
                ready_queue[rq_rear] = current;
                rq_rear = (rq_rear + 1) % MAX_PROCESSES;
                rq_size++;
            }
        }

        now = end;

        /* pick next and count context switch if real->real change */
        int prev = current;
        current = -1;

        if (rq_size > 0) {
            current = ready_queue[rq_front];
            rq_front = (rq_front + 1) % MAX_PROCESSES;
            rq_size--;

            if (prev != -1 && current != -1 && prev != current) {
                context_switches++;
            }

            if (processes[current].initial_schedule_time == -1) {
                processes[current].initial_schedule_time = now;
            }
        }
    }

    for (int i = 0; i < process_count; i++) {
        int resp = processes[i].initial_schedule_time - processes[i].arrival_time;
        int turn = processes[i].completion_time - processes[i].arrival_time;
        sum_response += resp;
        sum_turnaround += turn;
    }

    printf("\nRR Execution Completed.\n");
    printf("Average Response Time:  %.2f ms\n", sum_response / process_count);
    printf("Average Turnaround Time: %.2f ms\n", sum_turnaround / process_count);
    printf("Total Context Switches: %d\n\n", context_switches);
}