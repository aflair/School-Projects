/*
Andrew Flair
aflair
ECE 2220
1/19/2015

Programming Assignment 1

Purpose:
This program is for the 'Dabo' board game. The
game consists of a 4x4 board with a free space
randomly chosen every round. The user is prompted
to input a row and column in which to put a 'CU'
in a blank space. The user can quit at any time
and wins when they get 4 in a row. They can then
restart if they wish to or end the program.

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bprint(int b[4][4]);

int winfunc(int b[4][4]);

int main(void) {

	int x = 1;

// While loop for entire program incase of restart
	while (x != 0) {

		srand (time(NULL)); // Seed rand()
		int rrow,rcol; // declare initial variables

		rrow = rand() % 4; // Randomize row/column freespace
		rcol = rand() % 4;

		int board[4][4];
		int i,j;

// Initialize board values (0 = blank, 1 = CU, 2 = FREE)
		for(i=0; i<4; i++){ // Set all board values to 0
			for(j=0; j<4; j++){
				board[i][j] = 0;
			}
		}
		board[rrow][rcol] = 2; // Set free space

// Initialize Input Variables
		char row[0];
		char col[0];
		int rown, coln;
		int inputcount = 0;

// Initial Board Print

		bprint(board);

// Start Game (win loop) [1 = win, 0 = continue]
		int win = 0;
		while(win == 0){

// Column Input Loop
			int o = 1;
			while(o == 1){
				printf("Enter a 'q' at any time to quit.\nEnter 'D', 'A', 'B', or 'O'\n");
				scanf("%s",col);
				int quit = strcmp(col, "q");
				int dabo0 = strcmp(col, "D");
				int dabo1 = strcmp(col, "A");
				int dabo2 = strcmp(col, "B");
				int dabo3 = strcmp(col, "O");
				if(quit == 0){
					exit(0);
				}
				else if(dabo0 == 0){
					coln = 0;
					o = 0;
				}
				else if(dabo1 == 0){
					coln = 1;
					o = 0;
				}
				else if(dabo2 == 0){
					coln = 2;
					o = 0;
				}
				else if(dabo3 == 0){
					coln = 3;
					o = 0;
				}
				else{
					printf("Incorrect value inputted. Try again.\n");
				}
			}// end column input loop

// Row Input Loop
			int j = 1;
			while(j == 1){
				printf("Enter '1', '2', '3', or '4'\n");
				scanf("%s",row);
				int quit = strcmp(row, "q");
				int rows0 = strcmp(row, "1");
				int rows1 = strcmp(row, "2");
				int rows2 = strcmp(row, "3");
				int rows3 = strcmp(row, "4");
				if(quit == 0){
					exit(0);
				}
				else if(rows0 == 0){
					rown = 0;
					j = 0;
				}
				else if(rows1 == 0){
					rown = 1;
					j = 0;
				}
				else if(rows2 == 0){
					rown = 2;
					j = 0;
				}
				else if(rows3 == 0){
					rown = 3;
					j = 0;
				}
				else{
					printf("Incorrect value inputted. Try again.\n");
				}
			}// end row input loop
			
			if(board[rown][coln] == 0){
				board[rown][coln] = 1; // if valid input, change board value
				bprint(board);
				win = winfunc(board); // win detection function
				inputcount++;
			}
			else if(board[rown][coln] == 1){
				printf("Space already taken. Try again.\n");
			}
			else if(board[rown][coln] == 2){
				printf("That is your free space. Try again.\n");
			}			
		


		}// end win loop


// Restart Prompt and Exit

		printf("\nDabo!\n\nIt took you %d inputs to win.\nDo you wish to restart? (1 = yes, 0 = no)\n",inputcount);
		scanf("%d",&x);
		if(x != 0 && x != 1){
			printf("Error, non 1 or 0 value entered. Closing Program.\n");
			exit(0);
		}

		
	} // while loop for restart
	return(0);
}

/*

Function Name: bprint
Author: Andrew Flair
Objective:
	This function takes a [4][4] integer array from main and
	uses the information to display the game board. A value
	of 0 in the array is printed '    ', a value of 1 is
	printed ' CU ', and a value of 2 is printed 'Free'.
	There is no value returned.

*/

void bprint(int b[4][4]){

	int i,j;
	printf("     D      A      B      O\n");
	printf("  -----------------------------\n");
	for(i=0; i<=3; i++){
		printf("%d | ",i+1);
		for(j=0; j<=3; j++){
			if(b[i][j] == 0){
				printf("    ");
			}
			if(b[i][j] == 1){
				printf(" CU ");
			}
			if(b[i][j] == 2){
				printf("Free");
			}
			printf(" | ");
		}
		if(i != 3){
			printf("\n  |------|------|------|------|\n");
		}
		if(i == 3){
			printf("\n");
		}
	}
	printf("  -----------------------------\n");


}

/*

Function Name: winfunc
Author: Andrew Flair
Objective:
	This function takes a [4][4] integer array and
	detects whether a row, column, diagonal, or all
	corners contain either a 1 or a 2. If this 
	condition is true the function returns a 1. If
	not, the function returns a 0.

*/

int winfunc(int b[4][4]){
	int win = 0;
	// row win detection
	if(b[0][0] != 0 && b[0][1] != 0 && b[0][2] != 0 && b[0][3] != 0){
		win = 1;
	}
	else if(b[1][0] != 0 && b[1][1] != 0 && b[1][2] != 0 && b[1][3] != 0){
		win = 1;
	}
	else if(b[2][0] != 0 && b[2][1] != 0 && b[2][2] != 0 && b[2][3] != 0){
		win = 1;
	}
	else if(b[3][0] != 0 && b[3][1] != 0 && b[3][2] != 0 && b[3][3] != 0){
		win = 1;
	}
	// column win detection
	else if(b[0][0] != 0 && b[1][0] != 0 && b[2][0] != 0 && b[3][0] != 0){
		win = 1;
	}
	else if(b[0][1] != 0 && b[1][1] != 0 && b[2][1] != 0 && b[3][1] != 0){
		win = 1;
	}
	else if(b[0][2] != 0 && b[1][2] != 0 && b[2][2] != 0 && b[3][2] != 0){
		win = 1;
	}
	else if(b[0][3] != 0 && b[1][3] != 0 && b[2][3] != 0 && b[3][3] != 0){
		win = 1;
	}
	// diagonal win detection
	else if(b[0][0] != 0 && b[1][1] != 0 && b[2][2] != 0 && b[3][3] != 0){
		win = 1;
	}
	else if(b[0][3] !=0 && b[1][2] != 0 && b[2][1] != 0 && b[3][0] != 0){
		win = 1;
	}
	// corner win detection
	else if(b[0][0] !=0 && b[0][3] != 0 && b[3][0] != 0 && b[3][3] != 0){
		win = 1;
	}
	else{
		win = 0;
	}

	return(win);
}


