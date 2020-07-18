///////////////////////////////////////////////////////////////////////////////////
// School:      Brno University of Technology, Faculty of Electrical Engineering //
// Course:	BPC-P1CT							 //
// Project:     #8 Sudoku  							 //
// Module:      Different tools							 //
// Authors:     Artem Denisov	(xdenis00)					 //
//              Alkanan Tarik	(xalkanan02)					 //
///////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define CHECK_VALUE 45
#define FILENAME_LENGTH 50
#define END_GAME 99

/// Counts rows of the loaded game file
int count_rows(FILE *file);
/// Counts columns of the loaded game file
int count_columns(FILE *file);
/// Prints the current game board
void print_board(int **matrix, int rows, int columns);
/// Loads a file with a prepared game board 
int **load_game(FILE *file, int rows, int columns);
/// Saves a game board to file
void save_game(int **matrix, int rows, int columns);
/// Creates a new game
int **new_game(int rows, int columns);
/// Prints an error message, if the board contains it.
void error();
/// Checks the game board for errors and empty fields 
int check_board(int **matrix, int rows, int columns, int game_mode);
/// Finishes the game
void end_game(int **matrix, int rows, int columns, int size);
/// Starts the game
int **start_game(int **matrix, int rows, int columns, int size);