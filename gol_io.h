#ifndef __GOL_IO__
#define __GOL_IO__

/** gol_io.h - November 24, 2024 - Ethan Perry
 * This file reads the file, and has functionality to create and display boards.
 * The file is read, a board is initialized, and the coordinate inputs from the 
 * input file and then coded as 1's for a live cell to start the game. Functionality
 * to create, print, and delete a board are here to help facilitate the simulation.
 */

extern int TOTAL_CELLS;
extern int ROUND_CELLS;

/** read_file(char*, int*, int*, int*);
 * Read file opens a file pointer to a valid input file (see check_file for validation).
 * The number of rows, cols, and iterations for the simulation are read in from the first
 * three lines of the file. The int* passed into the function point to these values so they
 * can be later referenced and used back in main. A 2D board array is allocated and data
 * is read in line by line until end of file (see create_empty_board for more details).
 * Then, the board is returned (int**)
 * @param filename: the string containing the name of the user input file.
 * @param prow: pointer to the integer storing number of rows for the board.
 * @param pcol: pointer to the integer storing number of cols for the board.
 * @param psim: pointer to the integer storing number of iterations for the simulation.
 * @return: 2D int array storing all the board information from the input file.
 */
int** read_file(char*, int*, int*, int*);

/** create_empty_board(int, int)
 * Create empty board takes in dimension input for a ROWxCOL grid, 2D array.
 * A double for loop initializes and allocates the board, filling every grid
 * position with 0's.
 * @param: integer value storing number of rows for the board.
 * @param: integer value storing number of cols for the board.
 * @return: int** of the 2D int array storing the empty board (RxC) of all 0's.
 */
int** create_empty_board(int, int);

/** print_board(int**, int, int);
 * Print board takes in a int** 2D array (board), along with its dimensions
 * to output to the user. The board is coded using 0/1's integers but the output
 * will be done using some characters to enhance the output experience. 
 * 0 = '-' and 1 = '@'
 * @param: int** storing the 2D integer array board.
 * @param: integer value storing number of rows for the board.
 * @param: integer value storing number of cols for the board.
 * @return NULL
 */
void print_board(int**, int, int);

/** free_array(int***, int);
 * Free array takes a pointer to a 2D int array (int**) and the number of rows in that
 * given 2D array (board). It loops through each row and frees the array. Once every row
 * of the board is free, thereby freeing all the data from the board, the array itself
 * is deallocated. 
 * Note: I was getting a bizarre error when passing board without a pointer, so this is
 * the solution I knew would work, and ultimately did work. 
 * @param: a pointer to int** array (board).
 * @param: int storing the number of rows for the given board.
 * @return NULL
 */
void free_array(int***, int);

#endif