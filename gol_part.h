#ifndef __GOL_PART__
#define __GOL_PART__

/** gol_part.h - November 24, 2024 - Ethan Perry
 * This file contains functions that handle the partitioning of the game board, threading logic,
 * and printing of simulation data for the GOL simulation. The functions facilitate the division
 * of the game board among multiple threads, execution of the simulation by each thread, and
 * output of relevant simulation statistics.
 */

// declare extern global variables 
extern int TOTAL_CELLS;
extern pthread_barrier_t bar;
extern pthread_mutex_t mutex;

/** create_partition()
 * This function divides a given dimension (number of rows or columns) into partitions 
 * to be processed by multiple threads. Each partition's start and end indices are calculated 
 * and stored in the provided pointers. The function ensures that the remainder is evenly distributed.
 * The function dynamically allocates memory for the start and end indices arrays. 
 * These arrays should be freed by the caller to avoid memory leaks.
 * 
 * @param nthreads Number of threads to create partitions for.
 * @param rowcol Total number of rows or columns to be divided among threads.
 * @param pstarts Pointer to store the start indices of each partition.
 * @param pends Pointer to store the end indices of each partition.
 * @return NULL
 */
void create_partition(int, int, int**, int**);

/** print_thread_data()
 * This function prints the thread ID and the start and end coordinates of the segment
 * that the thread is processing. The output includes the row and column ranges and their
 * respective lengths. The formatted output string is then flushed to ensure it is
 * immediately written to the standard output. This function ensures that the output 
 * is formatted and flushed to standard output.
 *
 * @param coords Pointer to an array storing the start and end coordinates of the segment.
 * @param tid The ID of the thread.
 * @return NULL
 */
void print_thread_data(int*, int);

/** printf_data()
 * This function calculates and prints the total elapsed time for the simulation, the total number 
 * of live cells, and details about the thread configuration and board dimensions. It ensures the 
 * output is formatted nicely for easy readability. This function dynamically allocates memory 
 * for formatting the output lines and ensures it is freed after use to avoid memory leaks.
 *
 * @param start The start time of the simulation.
 * @param end The end time of the simulation.
 * @param row The number of rows in the board.
 * @param col The number of columns in the board.
 * @param iters The number of iterations the simulation ran.
 * @param direction The direction of partitioning (1 for row-wise, 0 for column-wise).
 * @param nthreads The number of threads used in the simulation.
 * @return NULL
 */
void print_data(struct timeval, struct timeval, int, int, int, int, int);

/** thread function
 * This function is executed by each thread. It initializes necessary variables, captures 
 * the start time, and calls the function to simulate a segment of the Game of Life board.
 * The printing/timing thread (tid 0) captures the end time and prints the final board and
 * simulation data after the simulation is complete.
 * The function uses the system call `system("clear")` to clear the screen and `gettimeofday`
 * to capture the start and end times of the simulation. It ensures proper synchronization 
 * and data integrity using pthread barriers and mutexes.
 * 
 * @param arg A void pointer to a ThreadData structure containing the thread-specific data.
 * @note see the gol_struct.h for information regarding variables
 * @return NULL
 */
void* thread_function(void*);

#endif