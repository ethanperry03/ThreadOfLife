#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "gol_sim.h"
#include "gol_io.h"
#include "gol_struct.h"

void simulate_board_segment(void* arg) {
    struct ThreadData* thread_data = (struct ThreadData*)arg;

    // store all data from the struct in local variables
    int tid = thread_data->tid;
    int row = thread_data->row;
    int col = thread_data->col;
    int wrap = thread_data->wrap;
    int show = thread_data->show;
    int speed = thread_data->speed;
    int iters = thread_data->iterations;

    // pointer to array storing coordinates for board segmenet
    int* coords = thread_data->coords;

    // pointers to boards
    int** board = thread_data->board;
    int** newboard = thread_data->newboard;

    int count = 0;  
    
    // while iter is in range
    while(count < iters) {
        // if it is the designated printing thread
        if (tid == 0) {
            // if program is showing output
            if (show == 1) {
                // print the board
                print_board(board, row, col);
                // live cell count for ith iteration
                printf("There are %d live cells\n", ROUND_CELLS);
                // sleep for 1/fps * 10^6
                usleep((1.0/speed)*1000000);
                // clear screen
                system("clear");  
            }
            // update global variables
            pthread_mutex_lock(&mutex);
            TOTAL_CELLS = TOTAL_CELLS + ROUND_CELLS;
            ROUND_CELLS = 0;
            pthread_mutex_unlock(&mutex); 
        }
        // wait for global variable to be reset before assessing it in update functions
        pthread_barrier_wait(&bar);

        // update the board
        if (wrap == 1) {
            update_wrap_segment(board, newboard, coords, row, col);
        }
        else if (wrap == 0) {
            update_nowrap_segment(board, newboard, coords, row, col);
        }

        // swap the boards using pointers
        swap_board(&board, &newboard);
        // wait for all threads to have swapped their boards
        pthread_barrier_wait(&bar);
        
        // update counter
        count = count + 1;
    } 
    // outside of while, print final board iteration
    if (tid == 0) {      
        system("clear");      
        print_board(board, row, col);
        printf("There are %d live cells\n\n", ROUND_CELLS);
    }      
}

void update_wrap_segment(int** old, int** new, int* coords, int row, int col) {
    int sum = 0;
    int cellCount = 0;

    // check the board / check the interior if wrapped
    for(int r = coords[0]; r < coords[1]+1; r++) {
        for(int c = coords[2]; c < coords[3]+1; c++) {
            sum = old[(r-1+row)%row][(c-1+col)%col] + old[r][(c-1+col)%col] + 
                  old[(r+1+row)%row][(c-1+col)%col] + old[(r-1+row)%row][c] + 
                  old[(r+1+row)%row][c] + old[(r-1+row)%row][(c+1+col)%col] + 
                  old[r][(c+1+col)%col] + old[(r+1+row)%row][(c+1+col)%col] ;
            new[r][c] = judgement_day(sum, old[r][c]);
            if (new[r][c] == 1) {
                cellCount++;
            }
        }
    }
    pthread_mutex_lock(&mutex);
    ROUND_CELLS = ROUND_CELLS + cellCount;
    pthread_mutex_unlock(&mutex); 
}

void update_nowrap_segment(int** old, int** new, int* coords, int row, int col) {
    int sum;
    int cellCount = 0;
    // check the board / check the interior if wrapped
    for(int r = coords[0]; r < coords[1]+1; r++) {
        for(int c = coords[2]; c < coords[3]+1; c++) {
            sum = 0;
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <=1; j++) {
                    if(r+i >= 0 && r+i < row && c+j >= 0 && c+j < col) {
                        sum = sum + old[r+i][c+j];
                    }
                }
            }
            // remove the middle
            sum = sum - old[r][c];
            // update new value
            new[r][c] = judgement_day(sum, old[r][c]);
            // update live cell counter
            if (new[r][c] == 1) {
                cellCount++;
            }
        }
    }
    pthread_mutex_lock(&mutex);
    ROUND_CELLS = ROUND_CELLS + cellCount;    
    pthread_mutex_unlock(&mutex); 
}

void swap_board(int*** old, int*** new) {
    // new board pointer has the data in old
    int** temp = *old;
    // old is now pointing at new
    *old = *new;
    // new is now pointing at old
    *new = temp;
}

int judgement_day(int sum, int oldVal) {
    int returnVal;
    // dies from loneliness
    if (sum < 2 && oldVal == 1) {
        returnVal = 0;
    }
    // overpopulation
    else if (sum > 3 && oldVal == 1) {
        returnVal = 0;
    }
    // good living conditions
    else if ((sum == 2 || sum == 3) && oldVal == 1) {
        returnVal = 1;
    }
    // repopulation
    else if (sum == 3 && oldVal == 0) {
        returnVal = 1;
    }
    // no change
    else {
        returnVal = oldVal;
    }
    // return dead/alive status
    return returnVal;
}