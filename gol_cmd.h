#ifndef __GOL_CMD__
#define __GOL_CMD__

/** gol_cmd.h - November 24, 2024 - Ethan Perry
 * 
 * Command line parsing and validation for Game of Life simulation. 
 * This file contains functions for parsing command line arguments and validating 
 * input parameters. The main parse_cmd function takes in all the input parameters
 * and calls their respective helper functions to check for valid input. If any of
 * the lines are invalid, the program throws an error.
 * 
 * Every validation function has a similar structure. To explain, take the check_wrap
 * function. The input string is read in, if the value is "wrap", then a 1 is returned,
 * if the value is "nowrap", then a 0 is returned. Else, invalid input error and the
 * program stops with an error message.
 * 
 * The command line arguments are expected in the following format: 
 * <executable> <input_file> <threads> <row/col> <wrap/nowrap> <show/hide> [speed] 
 */


/** parse_cmd(int, char**, char**, int*, int*, int*);
 * Parse command line function takes in the argv/argc values from user input, and acts
 * as a hub function to error check all the input, and return all the data to main (by pointer)
 * 
 * @param argv: the number of arguments given in the command line .
 * @param argc: the array of strings containing all of the text given in the command line.
 * @param infile: a pointer to a string that will point to user input file string.
 * @param pwrap: int pointer to return wrap code value to main.
 * @param pshow: int pointer to return show code value to main.
 * @param pspeed: int pointer to return speed code value to main.
 * @return: 0 if all input was sucessful, -1 if any portion of error checking failed.
 */
void parse_cmd(int, char**, char**, int*, int*, int*, int*, int*);

/** check_file(char*);
 * This function checks that the cmd line input for the file name is inputted
 * correctly by the user. A file pointer is initialized, and if not valid, 
 * the program prints and error and returns the error flag value of -1. If
 * the file name is valid, the program continues
 * @param filename: string containing the user input file name.
 * @return returnVal: 0 for succesful file opening, -1 for failure.
 */
void check_file(char*);

/** check_threads(char*);
 * This function checks that the cmd line input for the amount of threads
 * is entered correctly by the user. The string is converted to an int, 
 * then checked to be greater than 0. If not, error is thrown.
 * @param threadStr: string containing int number of threads.
 * @return threadNum: returns the number of threads to start as an int.
 */
int check_threads(char*);

/** check_rowcol(char*);
 * This function checks that the cmd line input for the direction of 
 * partitioning is entered correctly by the user. The string is either
 * "row" = 1, "col" = 0, or error is thrown. 
 * @param rowORcol: string storing the partition direction string.
 * @return rowcolVal: returns the coded value for partition direction.
 */
int check_rowcol(char*);

/** check_wrap(char*);
 * Check wrap reads the commnand line argument dictating wrap/nowrap for the game.
 * wrap = 1, nowrap = 0, failure = -1
 * @param wrapString: string containing user input string for wrapping value.
 * @return wrapVal: indicated wrap/nowrap or error value of -1.
 */
int check_wrap(char*);

/** check_show(char*);
 * Check show reads the commnand line argument dictating show/hide for the output.
 * show = 1, hide = 0, failure = -1
 * @param showString: string containing user input string for show/hide value.
 * @return showVal: indicated show/hide (1/0) or error value of -1.
 */
int check_show(char*);

/** check_speed(char*, int);
 * Check speed reads the commnand line argument dictating the speed as well as the
 * the show value. If show is 0 (hide), then no speed param is needed. There is an error
 * given is the user inputted hide and a speed. If the user inputted show, then the proper
 * checking of speed is done. slow = 3fps, med = 10fps, fast = 30fps
 * @param speedString: string containing user input string for speed value (slow/med/fast).
 * @param showVal: does this given input command line want to show the simulation given a speed.
 * @return speedVal: indicated the frame per second rate for the speed, if provided correctly, 
 * and -1 if hide (speed) or show (invalid speed) was entered.
 */
int check_speed(char*, int);

#endif