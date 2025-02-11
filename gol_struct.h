#ifndef __GOL_STRUCT__
#define __GOL_STRUCT__

/** ThreadData Struct
 * This structure stores all necessary data for each thread to process a segment of the 
 * GOL board, including thread-specific information, board dimensions, and simulation parameters.
 *
 * @var nthreads: Number of threads used in the simulation.
 * @var tid: The ID of the thread.
 * @var coords: Pointer to an array storing the coordinates (start and end points) of the segment.
 * @var row: The number of rows in the board.
 * @var col: The number of columns in the board.
 * @var board: Pointer to the current state of the board (2D array).
 * @var newboard: Pointer to the next state of the board (2D array).
 * @var wrap: A flag indicating if the board should wrap around the edges (1) or not (0).
 * @var show: A flag indicating if the board should be displayed after each iteration (1) or not (0).
 * @var speed: The speed of the simulation in frames per second (used only if show is 1).
 * @var iterations: The number of iterations to simulate.
 * @var direction: The direction for processing the board segment (row-wise or column-wise).
 */
struct ThreadData {
    int nthreads;
    int tid;
    int* coords;
    int row;
    int col;
    int** board;
    int** newboard;
    int wrap;
    int show;
    int speed;
    int iterations;
    int direction;
};

#endif