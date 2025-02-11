#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gol_io.h"

int** read_file(char* filename, int* prow, int* pcol, int* psim) {
     // open file to read, know it's valid from earlier cmd line parse check
    FILE* infile = fopen(filename, "r");

    // check pointer is valid
    if (infile == NULL) {
        printf("Invalid input file, please try again\n");
        exit(-1);
    }

    // read in top three values from file
    fscanf(infile, "%d\n", prow);
    fscanf(infile, "%d\n", pcol);
    fscanf(infile, "%d\n", psim);

    // create an empty board
    int** tempBoard = create_empty_board(*prow, *pcol);

    int tempRow, tempCol;
    // while the line of the file you read has exactly two data items
    while (fscanf(infile, "%d %d\n", &tempRow, &tempCol) == 2) {
        tempBoard[tempRow][tempCol] = 1;
        ROUND_CELLS = ROUND_CELLS + 1;
    }
    TOTAL_CELLS = ROUND_CELLS;

    // close file pointer
    fclose(infile);
    // return int** (2d) board array
    return tempBoard;
}

int** create_empty_board(int row, int col) {
    // create board with empty 0's with given row x col
    int** tempBoard = malloc(row * sizeof(int*));
    for(int r = 0; r < row; r++) {
        // loop through and create array at each pointer in tempBoard
        int* temp = malloc(col * sizeof(int));
        // fill the array with 0's
        for(int c = 0; c < col; c++) {
            temp[c] = 0;
        }
        // put temp array at row r
        tempBoard[r] = temp;
    }
    // return board
    return tempBoard;
}

void print_board(int** board, int row, int col) {
    // loop through each data item (either a 0 or 1)
    for (int r = 0; r < row; r++) {
        // if grid cell data is 1, print @, else print -
        for (int c = 0; c < col; c++) {
            if (board[r][c] == 1)
                printf("%c", '@');
            else
                printf("%c", '-');
        }
        printf("\n");
    }
}

void free_array(int*** array, int row) {
    // loop through number of rows of this board
    for(int i = 0; i < row; i++) {
        // free array at row 'r'
        free(array[0][i]);
    }
    // free entire array
    free(*array);
}