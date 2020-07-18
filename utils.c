///////////////////////////////////////////////////////////////////////////////////
// School:      Brno University of Technology, Faculty of Electrical Engineering //
// Course:	BPC-P1CT							 //
// Project:     #8 Sudoku  							 //
// Module:      Different tools							 //
// Authors:     Artem Denisov	(xdenis00)					 //
//              Alkanan Tarik	(xalkanan02)					 //
///////////////////////////////////////////////////////////////////////////////////

#include "utils.h"

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

int check_board(int **matrix, int rows, int columns, int size){
	int check_rows = 0;
	int check_columns = 0;
	int check_square = 0;

	if (size == 2){ // 9x9
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