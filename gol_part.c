#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include "gol_io.h"
#include "gol_struct.h"
#include "gol_sim.h"

void create_partition(int nthreads, int rowcol, int** pstarts, int** pends) {
    // declare arrays to store the start and end indecises
    int* starts = malloc(nthreads * sizeof(int));
    int* ends = malloc(nthreads * sizeof(int));

    // hard code the first start and the last end (always known)
    starts[0] = 0;
    ends[nthreads-1] = rowcol - 1;

    // define the remainder and the mod whole number
    int remain = rowcol % nthreads;
    int chunk = rowcol / nthreads;
    int val;

    // loop through to assign the remainder evenly and store indeces
    for (int i = 1; i < nthreads; i++) {
        val = chunk;
        // if there is remainder, assign it
        if (remain > 0) {
            val = val + 1;
            remain = remain - 1;
        }
        // store vals
        starts[i] = val + starts[i-1];
        ends[i-1] = starts[i] - 1;
    }
    
    // assign pointers to pass by pointer
    *pstarts = starts;
    *pends = ends;
}

void print_data(struct timeval start, struct timeval end, int row, int col, int iters, int direction, int nthreads) {
        // Calculate the elapsed time in seconds and microseconds
        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        // If the end microseconds are smaller than the start microseconds, adjust the seconds
        if (microseconds < 0) {
            seconds--;
            microseconds += 1000000;
        }
                  
        // output length of simulation in nice output
        printf("Total of %d live cells during the simualation\n", TOTAL_CELLS);
        printf("Total time for %d iterations of %dx%d is %.6f\n\n", iters, row, col, seconds + microseconds/1000000.0);    
        
        // store the row or col output string
        char directionString[4];
        if (direction == 1) { strcpy(directionString, "row"); }
        else { strcpy(directionString, "col"); }
        directionString[3] = '\0';

        int width = 50;
        char* line = malloc(width + 1);
        memset(line, '-', width);
        line[width] = '\0';
        
        printf("#%d threads, %s-wise partitioning\n", nthreads, directionString);
        printf("%s\n", line);

        free(line);
}

void print_thread_data(int* coords, int tid) {
    // print formatted output string for each thread and flush out std
    printf("tid: %2d | rows: %3d-%-3d (%d) | cols: %3d-%-3d (%d)\n",
            tid, coords[0], coords[1], coords[1] - coords[0] + 1, 
            coords[2], coords[3], coords[3] - coords[2] + 1);
    fflush(stdout);
}

void* thread_function(void* arg) {
    struct ThreadData* thread_data = (struct ThreadData*)arg;

    int nthreads = thread_data->nthreads;
    int tid = thread_data->tid;
    int row = thread_data->row;
    int col = thread_data->col;
    int iters = thread_data->iterations;
    int direction = thread_data->direction;

    // int** board = thread_data->board;

    // start clock object
    struct timeval start, end;

    // if you are the printing/timing thread
    if (tid == 0) {
        // clear away system to start output
        system("clear");
        // capture time of day
        gettimeofday(&start, NULL);
    }

    // send threads to simulate thier segment of the board
    simulate_board_segment(arg);

    // print final board after simulation is done
    if (tid == 0) {
        // stop clock and calculate how long it has been
        gettimeofday(&end, NULL);

        // print a space and then the final board
        // print_board(board, row, col);   

        // send printing thread to print all of this stuff
        print_data(start, end, row, col, iters, direction, nthreads);
    }

    return NULL;
}