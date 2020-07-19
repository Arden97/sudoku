///////////////////////////////////////////////////////////////////////////////////
// School:      Brno University of Technology, Faculty of Electrical Engineering //
// Course:	BPC-P1CT							 //
// Project:     #8 Sudoku  							 //
// Module:      Main module							 //
// Authors:     Artem Denisov	(xdenis00)					 //
//              Alkanan Tarik	(xalkanan02)					 //
///////////////////////////////////////////////////////////////////////////////////

#include "./utils/utils.h"

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
			else {
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
		case 'y': goto start;
		case 'n': printf("Have a nice day :)\n"); exit(1);
		default: goto again;
	}
}
