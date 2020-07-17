///////////////////////////////////////////////////////////////////////////////////
// School:      Brno University of Technology, Faculty of Electrical Engineering //
// Course:	BPC-P1CT							 //
// Project:     #8 Sudoku  							 //
// Module:      Main module							 //
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

int count_rows(FILE *file){
	int rows = 0;
	char c;
	while((c = fgetc(file)) != EOF) {
		if(c == '\n') rows++;
	}
	fseek(file, 0, SEEK_SET);
	return rows+1;
}

int count_columns(FILE *file){
	int columns = 0;
	int c;
	while ((c = fgetc(file)) != '\n' && (c != EOF)){
		if(isdigit(c)) columns++;
	}
	fseek(file, 0, SEEK_SET);
	return columns;
}

void print_board(int **matrix, int rows, int columns){
	putchar('\n');
	for(int i = 0; i<rows; i++){
		for(int j = 0; j<columns; j++){
			if(matrix[i][j] == 0) printf("| ");
			else printf("|%d", matrix[i][j]);
		}
		printf("|\n");
	}
	putchar('\n');
}

int **load_game(FILE *file, int rows, int columns){
	int **matrix = (int **)malloc(rows * sizeof(int *));
	for (int i=0; i<rows; i++) 
        matrix[i] = (int *)malloc(columns * sizeof(int));

	for(int i = 0; i<rows; i++){
		for(int j = 0; j<columns; j++){
	 		fscanf(file, "%d", &matrix[i][j]);
	 	}
	}
	print_board(matrix, rows, columns);
	return matrix;
}

void save_game(int **matrix, int rows, int columns){
	FILE *file;
	char name[FILENAME_LENGTH];
save:
	printf("Enter save name: ");
	scanf(" %s", &name);
	file = fopen(name, "w");
	if(file == NULL){
		printf("Unable to create file. Please, try again\n");
		goto save;
	}

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < columns; j++){	
			fprintf(file, "%d", matrix[i][j]);
			if(j != columns-1) fprintf(file, " ");
		}
		if(i != rows-1) fprintf(file, "\n");
	}
	fclose(file);
}

int **new_game(int rows, int columns){
	int **matrix = (int **)malloc(rows * sizeof(int *));
	for (int i=0; i<rows; i++)
    	matrix[i] = (int *)malloc(columns * sizeof(int));
	
	for(int i = 0; i<rows; i++){
		for(int j = 0; j<columns; j++){
			printf("Enter a value of [%d][%d] ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	print_board(matrix, rows, columns);
	return matrix;
}

void error(){
	printf("\nERROR: The desk contains errors or blank fields\n\n");
}

int check_board(int **matrix, int rows, int columns, int game_mode){
	int check_rows = 0;
	int check_columns = 0;
	int check_square = 0;

	if (game_mode == 2){ // 9x9
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < columns; j++){
				check_rows = matrix[i][j] + check_rows;
				check_columns =+ matrix[j][i] + check_columns;
			}
			if (check_rows != CHECK_VALUE || check_columns != CHECK_VALUE){
				error();
				return 0;
			}
			check_rows = 0;
			check_columns = 0;
		}
	}
	else{ // 3x3
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < columns; j++){
				check_square = matrix[i][j] + check_square;
			}
		}
		if (check_square != CHECK_VALUE){
			error();
			return 0;
		}
	}
	printf("Everything is correct\n\n");
	return 1;
}

void end_game(int **matrix, int rows, int columns, int size){
	char answer;
	printf("Would you like to save the game? [y/n] ");
	scanf(" %c", &answer);
	if (answer == 'y'){
		save_game(matrix, rows, columns);
	}
	putchar('\n');
	printf("Would you like to check your game? [y/n] ");
	scanf(" %c", &answer);
	if (answer == 'y'){
		check_board(matrix, rows, columns, size);
	}
}

int **start_game(int **matrix, int rows, int columns, int size){
	int row, column;
cell:
	printf("\nWhich cell would you like to change? [end game - 99]\n");
	printf("Row: "); scanf("%d", &row);
	if (row == END_GAME){
		end_game(matrix, rows, columns, size);
		return 1;
	}
	
	printf("Column: "); scanf("%d", &column);
	if (matrix[row][column] == 0){
		printf("Enter a value: ");
		scanf("%d", &matrix[row][column]);
		print_board(matrix, rows, columns);
		goto cell;
	}
	else{
		printf("You can't change this cell.\n");
		goto cell;
	}
}


/* Main function */
int main(int argc, char** argv){
	int **matrix;
	FILE *file;
	char filename[FILENAME_LENGTH];
	int rows;
	int columns;
	int size;
	int game_mode;
	char answer;

	printf("Welcome to Sudoku!\n\n");
start:	
	printf("Please, select a game mode [1 - new game, 2 - load game]: ");
	scanf("%d", &game_mode); putchar('\n');
	switch(game_mode){
		case 1:
			printf("Select the size of the board [1 - 3x3, 2 - 9x9] ");
			scanf("%d", &size);
			if (size == 1){
				rows = 3;
				columns = 3;
			}
			else if(size == 2){
				rows = 9;
				columns = 9;
			}
			matrix = new_game(rows, columns);
			break;
		case 2:
			printf("Enter the name of the saved game: ");
			scanf(" %s", &filename); putchar('\n');
			file = fopen(filename, "r");

			rows = count_rows(file);
			columns = count_columns(file);
			if (rows == 3 && columns == 3) size = 1;
			else if(rows == 9 && columns == 9) size = 2;
			else{
				printf("The game supports only 3x3 and 9x9 boards\n");
				exit(0);
			}
			matrix = load_game(file, rows, columns);
			fclose(file);
			break;
		default: printf("Wrong game mode. Please, try again\n\n"); goto start;
	}

	start_game(matrix, rows, columns, size);
	free(matrix);

again:	
	printf("Would you like to play again? [y/n] ");
	scanf(" %c", &answer); putchar('\n');
	switch(answer){
		case 'y': goto start; break;
		case 'n': printf("Have a nice day :)\n"); exit(1);
		default: goto again;
	}
}
