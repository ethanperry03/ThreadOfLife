/** gol.c - November 24, 2024 - Ethan Perry
 * Driver program for Conway's Game of Life simulation using multi-threading. 
 * This program is the main driver for running the simulation. It handles variable 
 * declarations, user input parsing, and overall execution flow. The program starts 
 * by parsing command line arguments to validate and extract necessary input parameters. 
 * It then reads the initial board state from the input file, partitions the board 
 * for multi-threaded processing, and initiates the simulation. Finally, it ensures 
 * proper synchronization between threads and outputs the results. 
 * @param argv: number of input arguments.
 * @param argc: string containing all cmd line arguments to be parsed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "gol_cmd.h"
#include "gol_io.h"
#include "gol_sim.h"
#include "gol_part.h"
#include "gol_struct.h"


int TOTAL_CELLS = 0;
int ROUND_CELLS = 0;
pthread_barrier_t bar;
pthread_mutex_t mutex;

int main(int argv, char** argc) {
    // declare data to hold cmd line information
    int nthreads, direction, wrap, show, speed;

    // input file pointer
    char* filename = NULL;
    
    // initialize int** to store board information after read file       
    int** board;
    int** newboard;
    
    // store information about the board dimensions and simulation steps
    int row, col, iter; 
    
    // int pointers to store the start and end bounds for threads
    int* starts;
    int* ends;

    // parse command line argument and store success/failure status
    parse_cmd(argv, argc, &filename, &nthreads, &direction, &wrap, &show, &speed);

    // read the file and return row, col, iter by reference, store board
    board = read_file(filename, &row, &col, &iter);
    newboard = create_empty_board(row, col);

    // create the partition arrays storing the start and end row/cols
    if (direction == 1 && nthreads <= row) {
        create_partition(nthreads, row, &starts, &ends);
    }
    else if (direction == 0 && nthreads <= col) {
        create_partition(nthreads, col, &starts, &ends);
    }
    else {
        printf("Error: more threads than there are rows/cols\n\n");
        exit(-1);
    }

    // define the struct data array and the shared synch. mechanisms
    struct ThreadData* thread_data = malloc(nthreads * sizeof(struct ThreadData));
    pthread_t* tids = malloc(nthreads * sizeof(pthread_t));
    pthread_barrier_init(&bar, NULL, nthreads);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    // loop through and create the threads
    for (int i = 0; i < nthreads; i++) {
        int* tempArr = malloc(4 * sizeof(int));
        if (direction == 1) {
            tempArr[0] = starts[i];
            tempArr[1] = ends[i];
            tempArr[2] = 0;
            tempArr[3] = col - 1;
        }
        else {
            tempArr[0] = 0;
            tempArr[1] = row - 1;
            tempArr[2] = starts[i];
            tempArr[3] = ends[i];
        }
        thread_data[i].nthreads = nthreads;
        thread_data[i].tid = i;
        thread_data[i].coords = tempArr;
        thread_data[i].row = row;
        thread_data[i].col = col;
        thread_data[i].board = board;
        thread_data[i].newboard = newboard;
        thread_data[i].wrap = wrap;
        thread_data[i].show = show;
        thread_data[i].speed = speed;
        thread_data[i].iterations = iter;
        thread_data[i].direction = direction;
    }

    // loop through all of the thread data structs and create threads for each
    for (int i = 0; i < nthreads; i++) {
        pthread_create(&tids[i], NULL, thread_function, &thread_data[i]);
    }
    
    // join all the threads
    for (int i = 0; i < nthreads; i++) {
        pthread_join(tids[i], NULL);
        print_thread_data(thread_data[i].coords, thread_data[i].tid);
        free(thread_data[i].coords);
    }
    // print for end of sim formatting
    printf("\n");

    // deallocate data
    free(thread_data);
    free(tids);
    free(starts);
    free(ends);
    free_array(&board, row);
    free_array(&newboard, row);

    // destroy the pthread tools
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&bar);

    return 0;
}
