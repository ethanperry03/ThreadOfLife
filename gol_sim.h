#ifndef __GOL_SIM__
#define __GOL_SIM__

/** gol_sim.h - November 24, 2024 - Ethan Perry
 * The simulation file has a general function that simulates a portion of the game
 * board, given the start and end coordinates of the section you wish to simulate.
 * Based on a set of cmd line input parameters from the user, the simulation will
 * wrap/nowrap, show/hide the board for output display for the user. Synchronization
 * mechanisms are implemented to ensure the multi-threading occurs correctly
 */

// declare extern global variables 
extern int TOTAL_CELLS;
extern int ROUND_CELLS;
extern pthread_barrier_t bar;
extern pthread_mutex_t mutex;

/** simulate_board_segment(void*)
 * This function takes a void* pointer to a struct storing a variety of information
 * for the thread that is using this function. The simulation loop begins and based on
 * cmd line arguments, displays to the user (or not) and the board wraps (or not).
 * Once each thread is done with updating its own section of the board on the ith
 * iteration, a barrier catches all the threads while the boards are swapped. Once they
 * have been swapped, the global variables are updated and another barrier waits before
 * the i+1 iteration starts. This loops until the number of iterations is met.
 * @note: See struct.h for definitions of each variable in the threadData struct.
 * 
 * @param arg: this is the pointer to a struct argument being passed for each.
 * individual thread of the simulation.
 * @return NULL
 */
void simulate_board_segment(void*);

/** update_wrap_segment
 * Given data specifying which segment of the board to update, and other necessary
 * data to run the update, the rules of GOL are applied to the given segment. These
 * rules are applied assuming the board wraps around (like a taurus) and hence, there
 * are no boundary cases to worry about. This is implemented using %. After each cell
 * is inspected and the i+1 board is updated according to the rules, the global live
 * cell counter is updated, protected by a mutex.
 * 
 * @param old The current state of the board.
 * @param new The next state of the board.
 * @param coords Pointer to an array storing the coordinates of the segment to be processed.
 * @param row The number of rows in the board.
 * @param col The number of columns in the board.
 * @return NULL
 */
void update_wrap_segment(int**, int**, int*, int, int);

/** update_nowrap_segment
 * Given data specifying which segment of the board to update, and other necessary
 * data to run the update, the rules of GOL are applied to the given segment. These
 * rules are applied assuming the board does NOT wrap around. Therefore, there are
 * boundary cases to worry about. and more care is taken when calculating live cells. 
 * After each cell is inspected and the i+1 board is updated according to the rules,
 * the global live cell counter is updated, protected by a mutex.
 * 
 * @param old The current state of the board.
 * @param new The next state of the board.
 * @param coords Pointer to an array storing the coordinates of the segment to be processed.
 * @param row The number of rows in the board.
 * @param col The number of columns in the board.
 * @return NULL
 */
void update_nowrap_segment(int**, int**, int*, int, int);

/** swap_board(int***, int***);
 * swap board allows for the old board and 'flex' board to be swapped. This is useful so that
 * when calling update_board within the sim while loop, the code can always pass one board
 * and swap them after. The function uses int*** pointers so that nothing needs to be returned
 * and all that happens is a pointer swap.
 * @param old: address location of the old (Nth) board
 * @param new: address location of the new (N+1th) board 
 * @return NULL
 */
void swap_board(int***, int***);

/** judgement_day(int, int)
 * Judgement day (cleaverly named) is the function that handle each case for life/death.
 * See the rules for Conway's game of life for rules dictating life/death for next iter of board.
 * @param sum: Stores the number of live cells around the ith, jth cell to figure out state of next iter 
 * @param oldVal: stores old value of ith, jth cell to tell if it was alive or dead.
 * @return: this returns 1 if the cell is to be alive and 0 if the cell is dead in the next iteration.
 * @return NULL
 */
int judgement_day(int, int);

#endif