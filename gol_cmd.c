#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gol_cmd.h"

void parse_cmd(int argv, char** argc, char** infile, int* pthreads, int* prow, int* pwrap, int* pshow, int* pspeed) {
    // for formatting
    printf("\n");

    // Ensure all options are entered into command line
    if (argv < 6 || argv > 7) {
        printf("error: %d parameters received\nexpected -> five or six\n\n", argv - 1);
        exit(-1);
    }

    // set infile to expected file name from cmd line input
    *infile = argc[1];
    check_file(*infile);
    
    // store number of threads for the program
    int threadVal = check_threads(argc[2]);

    // store the code value for row/col
    int rowVal = check_rowcol(argc[3]);

    // store the wrap/nowrap input field is valid
    int wrapVal = check_wrap(argc[4]);
    
    // store the show/hide field is valid, collect speed if approp.
    int showVal = check_show(argc[5]);

    // error check if show was called without speed param
    int speedVal = 0;
    if (showVal == 1 && argv == 6){
        printf("error: no speed paramter was provided\n\n");
        exit(-1);
    }
    if (argv == 7) {
        speedVal = check_speed(argc[6], showVal);
    }

    // assign vals to pointers to return them "by reference"
    *pthreads = threadVal;
    *prow = rowVal;
    *pwrap = wrapVal;
    *pshow = showVal;
    *pspeed = speedVal;   
}

void check_file(char* filename) {
    // open file to read
    FILE* infile = fopen(filename, "r");
    // check if file pointer is null (indicating invalid file)
    if (infile == NULL) {
        printf("error: '%s' is an invalid file\n", filename);
        printf("ensure file exists and entered correctly\n\n");
        exit(-1);
    }
    // close file pointer
    fclose(infile);
}

int check_threads(char* threadStr) {
    // convert to int
    int threadNum = atoi(threadStr);

    // check if it is valid number of threads to start
    if (threadNum < 1) {
        printf("Invalid number of threads\n");
        printf("enter -> a number greater than 0\n\n");
        exit(-1);
    }

    // return number of threads back
    return threadNum;
}

int check_rowcol(char* rowORcol) {
    // coded val
    int rowcolVal;
    // if string was row, store a 1
    if (strcmp(rowORcol, "row") == 0) {
        rowcolVal = 1;
    }
    // else if string was nowrap, return a 0
    else if (strcmp(rowORcol, "col") == 0) {
        rowcolVal = 0;
    }
    // else invalid, print invalid input message
    else {
        printf("error: '%s' is not a valid 'direction' parameter\n", rowORcol);
        printf("enter -> (row/col)\n\n");
        exit(-1);
    }
    // return code
    return rowcolVal;
}

int check_wrap(char* wrapString) {
    // check first input part
    int wrapVal;
    // if string was wrap, return a 1
    if (strcmp(wrapString, "wrap") == 0) {
        wrapVal = 1;
    }
    // else if string was nowrap, return a 0
    else if (strcmp(wrapString, "nowrap") == 0) {
        wrapVal = 0;
    }
    // else invalid, print invalid input message
    else {
        printf("error: '%s' is not a valid 'wrap' parameter\n", wrapString);
        printf("enter -> (wrap/nowrap)\n\n");
        exit(-1);
    }
    // return code
    return wrapVal;
}

int check_show(char* showString) {
    int showVal;
    // Check if input param is show
    if(strcmp(showString, "show") == 0) {
        showVal = 1;
    }
    // else if, check if input param is hide
    else if (strcmp(showString, "hide") == 0) {
        showVal = 0;
    }
    // else, error
    else {
        printf("error: '%s' is not a valid 'show' parameter\n", showString);
        printf("enter -> (show/hide)\n\n");
        exit(-1);
    }
    // return code val
    return showVal;
}

int check_speed(char* speedString, int showVal) {
    int speedVal = 0;
    // if showval was 0 (hide) but you are checking speed, give error
    if (showVal == 0) {
        printf("error: hide does not take a speed parameter '%s'\n\n", speedString);
        speedVal = -1;
        exit(-1);
    }
    // else, show was called so speed is a valid input
    // see fps calculation within simulate_board in gol_sim.c
    else {
        // if speed is slow, fps = 3
        if (strcmp(speedString, "slow") == 0) {
            speedVal = 3;
        }
        // else if speed is medium, fps = 10
        else if (strcmp(speedString, "med") == 0) {
            speedVal = 10;
        }
        // else if speed is fast, fps = 30
        else if (strcmp(speedString, "fast") == 0) {
            speedVal = 30;
        }
        // else, error and print error message
        else {
            printf("error: '%s' is not a valid 'speed' parameter\n", speedString);
            printf("enter -> (fast/med/slow)\n\n");
            exit(-1);
        }
    }
    // return back the speed val code
    return speedVal;
}