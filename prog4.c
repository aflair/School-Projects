/*

aflair
prog4.c by Andrew Flair
ECE 2220 - Spring 2015
Programming Assignment 4
3/9/15

Purpose:

This program continuously scans for 1 of 6 commands. The
user can either: create a vector, create a matrix, add
two vectors, find the magnitude of a vector, multiply two
matrices together, or quit the program. Every command is
split up into a function (except quit) and details about
each command can be found in the information above the
function.

Assumptions:
- Since <math.h> is included one must compile with the -lm tag.
- Only matrices that have been created with this program can be used,
  unless the .txt file has the required metedata in the beginning.
- Vectors and matrices cannot have more than 32 rows or columns
- For the sake of continuity, vector/matrix names cannot exceed 32 characters
- Vectors and matrices must only contain floating point numbers (no text/symbols)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void vcreate(char *cols, char *name);

void mcreate(char *rows, char *cols, char *name);

void vadd(char *name1, char *name2);

void magfind(char *vectorname);

void mmultiply(char *name1, char *name2);

int main(void){

	int x;
	char input1[256];
	char *input2, *input3, *input4, *input5;

	
	x= 0;
	while(x != 1){
		
		// Clear input1
		memset(&input1[0], 0, sizeof(input1));
		// Allocate (and clear) memory for input with max of 32
		input2 = (char *)calloc(32, sizeof(char));
		input3 = (char *)calloc(32, sizeof(char));
		input4 = (char *)calloc(32, sizeof(char));
		input5 = (char *)calloc(32, sizeof(char));
		
		// Set all inputs to NULL to be able to recognize if input should be stored
		input2 = NULL;
		input3 = NULL;
		input4 = NULL;
		input5 = NULL;
		
		printf("Please Enter a Command:\n");
		scanf(" %[^\n]", input1); // Scans input of multiple words into one string
		
		// Copy first word ending with a space into input1 and rest into input2
		input2 = strchr(input1, ' '); 
		if(input2 != NULL) *input2++ = '\0';
		
		// Check to see if first word was quit
		if(strcmp(input1, "quit") == 0){
			printf("Exiting program.\n");
			x = 1;
			continue; // need to break while loop but not end program so program can free memory at end
		}
		
		// Seperates input2 into 4 seperate variables (input2, 3, 4, 5) for easy recognition
		if(input2 != NULL){
			input3 = strchr(input2, ' ');
			if(input3 != NULL) *input3++ = '\0';
			if(input3 != NULL){
				input4 = strchr(input3, ' ');
				if(input4 != NULL) *input4++ = '\0';
				if(input4 != NULL){
					input5 = strchr(input4, ' ');
					if(input5 != NULL) *input5++ = '\0';
				}
			}
		}


		
		// Check for the 'create' commands
		if((strcmp(input1, "create") == 0) && (input2 != NULL)){
			if((strcmp(input2, "vector") == 0) && (input3 != NULL) && (input4 != NULL)){
				vcreate(input3, input4);
				getchar();
			}
			else if((strcmp(input2, "matrix") == 0) && (input3 != NULL) && (input4 != NULL) && (input5 != NULL)){
				mcreate(input3, input4, input5);
				getchar();
			}
			else{
				printf("Invalid command.\n");
			}
		}
		
		// Check for 'add vectors' command
		else if((strcmp(input1, "add") == 0) && (input2 != NULL)){
			if((strcmp(input2, "vectors") == 0) && (input3 != NULL) && input4 != NULL){
				vadd(input3, input4);
			}
			else{
				printf("Invalid command. (Correct Usage: add vectors name1 name2)\n");
			}
		}
		
		// Check for the 'magnitude' command
		else if(strcmp(input1, "magnitude") == 0){
			if(input2 == NULL){
				printf("Invalid command, please specify a vector.\n");
			}
			else{
				magfind(input2);
			}
		}
		
		// Check for 'multiply matrices' command
		else if((strcmp(input1, "multiply") == 0) && (input2 != NULL)){
			if((strcmp(input2, "matrices") == 0) && (input3 != NULL) && (input4 != NULL)){
				mmultiply(input3, input4);
			}
			else{
				printf("Invalid command. (Correct Usage: multiply matrices name1 name2)\n");
			}
		}
		
		// Restart incase command was not recognized
		else{
			printf("Invalid command.\n");
		}

	}
	
	input2 = NULL;
	input3 = NULL;
	input4 = NULL;
	input5 = NULL;
	
	free(input2);
	free(input3);
	free(input4);
	free(input5);
				
	return 0;
}


/*
Function Name: vcreate()
Author: Andrew Flair
Purpose:

This program takes a number of columns and a name for a vector
to be created. It then creates a file based on the name and prompts
the user to store numbers into the vector based on how many columns
they previously specified. Since the vector is saved into a .txt
file, nothing is returned.

*/

void vcreate(char *cols, char *name){
	char *extension = ".txt";
	char filespec[strlen(name) + strlen(extension) + 1];
	FILE *output;
	int colnum, x;
	
	colnum = atoi(cols); // Convert cols string to int, returns 0 if cols is not an int
	
	// Check to see if cols was a valid input
	if((colnum <= 0) || (colnum > 32)){
		printf("Incorrect column input.\n\n");
		return;
	}
	
	float vector[colnum+1];
	
	// Prompt user to enter values for vector one by one
	printf("Creating Vector:\n\n");
	for(x = 0; x < colnum; x++){
		printf("Enter value for %s[%d]: ", name, x+1);
		scanf(" %f", &vector[x]);
	}
	
	snprintf(filespec, sizeof(filespec), "%s%s", name, extension); // Create .txt file based on user input 'name'
		
	output = fopen(filespec, "w");
	
	for(x = 0; x < colnum; x++){
		fprintf(output, "%f ", vector[x]);	// Copy newly created vector into .txt file
	}
	
	fclose(output);
	
	printf("Vector created into file %s.txt.\n\n", name);
	
	return;
}

/*
Function Name: mcreate()
Author: Andrew Flair
Purpose:

This program takes a number of rows and columns and a name for a
matrix to be created. It then creates a file based on the name and
prompts the user to store numbers into the matrix one by one based
on the previously specified size. Since the matrix is saved into a
.txt file, nothing is returned.

*/

void mcreate(char *rows, char *cols, char *name){
	char *extension = ".txt";
	char filespec[strlen(name) + strlen(extension) + 1];
	FILE *output;
	int colnum, rownum, i, j;
	
	colnum = atoi(cols); // Convert cols string to int, returns 0 if cols is not an int
	rownum = atoi(rows); // Convert rols string to int, returns 0 if rows is not an int
	
	// Check to see if rows and cols was a valid input
	if((colnum <= 0) || (colnum > 32)){
		printf("Incorrect column input.\n\n");
		return;
	}
	if((rownum <= 0) || (rownum > 32)){
		printf("Incorrect row input.\n\n");
		return;
	}
	
	float matrix[rownum+1][colnum+1];
	
	// Prompt user to input matrix values one by one
	printf("Creating Matrix:\n\n");
	for(i = 0; i < rownum; i++){
		for(j = 0; j < colnum; j++){
			printf("Enter value for %s[%d][%d]: ", name, i+1, j+1);
			scanf(" %f", &matrix[i][j]);
		}
	}
	
	snprintf(filespec, sizeof(filespec), "%s%s", name, extension); // Create .txt file based on user input 'name'
	
	output = fopen(filespec, "w");
	
	fprintf(output, "%d %d\n", i, j); // print size of matrix into first line of .txt file (metadata)
	
	// Copy matrix into the .txt file
	for(i = 0; i < rownum; i++){
		for(j = 0; j < colnum; j++){
			fprintf(output, "%f", matrix[i][j]);
			if(j != colnum-1) fprintf(output, " "); // add space unless last column
		}
		if (i != rownum-1) fprintf(output, "\n"); // add enter unless last row
	}
	
	fclose(output);
	
	printf("Matrix created into file %s.txt.\n", name);
	
	return;
}

/*
Function Name: vadd()
Author: Andrew Flair
Purpose:

This function takes in the names of 2 vectors. It then checks
to see if .txt files of both specified vectors exist and if
so it reads them into vector variables. The program checks to
see if the vectors are the same length and if so it adds them
into a result vector. The result vector is then printed to
stdout and the function returns nothing.

*/

void vadd(char *name1, char *name2){
	char *extension = ".txt";
	char file1[strlen(name1) + strlen(extension) + 1];
	char file2[strlen(name2) + strlen(extension) + 1];	
	FILE *out1, *out2;
	float vector1[33], vector2[33], result[33];
	int i = 0;
	int j = 0;
	int x;
	
	snprintf(file1, sizeof(file1), "%s%s", name1, extension); // Create .txt file based on user input 'name'
	snprintf(file2, sizeof(file2), "%s%s", name2, extension);
	
	out1 = fopen(file1, "r");
	out2 = fopen(file2, "r");
	
	// Check to see if file exists, if so read it into vector1
	if(out1 != NULL){
		while(fscanf(out1, "%f ", &vector1[i]) != EOF){
			i++;
		}
	}
	else{
		printf("Invalid name for file 1.\n\n");
		fclose(out1);
		fclose(out2);
		return;
	}
	
	// Check to see if file exists, if so read it into vector2
	if(out2 != NULL){
		while(fscanf(out2, "%f ", &vector2[j]) != EOF){
			j++;
		}
	}
	else{
		printf("Invalid name for file 2.\n\n");
		fclose(out1);
		fclose(out2);
		return;
	}
	
	// Check if vectors are not same length, return if they are not
	if(i != j){
		printf("Vectors are not the same length.\n\n");
		fclose(out1);
		fclose(out2);
		return;
	}
	
	// For loop to simultaneously add and print the resulting vector.
	printf("Vector %s + Vector %s Equals:\n\n", name1, name2);
	for(x = 0; x < i; x++){
		result[x] = vector1[x] + vector2[x];
		printf("Result[%d]: %f\n", x, result[x]);
	}
	printf("\n");
	
	fclose(out1);
	fclose(out2);
		
	return;
}

/*
Function Name: magfind()
Author: Andrew Flair
Purpose:

This function takes in the name of a vector. It then checks
to see if a .txt file exists with the specified name. If so
the function then calculates the magnitude of said vector
and prints the result to stdout. This function returns
nothing.

*/

void magfind(char *vectorname){
	char *extension = ".txt";
	char file[strlen(vectorname) + strlen(extension) + 1];
	FILE *out;
	int i = 0;
	int x;
	float vector[33];
	float squared = 0;
	float magnitude;
	
	snprintf(file, sizeof(file), "%s%s", vectorname, extension); // Create variable with vectorname.txt
	out = fopen(file, "r");
	
	// Check to see if vector file exists, if so read it into vector[]
	if(out != NULL){
		while(fscanf(out, "%f ", &vector[i]) != EOF){
			i++;
		}
	}
	else{
		printf("Invalid vector name.\n\n");
		fclose(out);
		return;
	}
	
	// Adds all vector values squared
	for(x = 0; x < i; x++){
		squared += pow(vector[x], 2);
	}
	
	// Takes square root of added squares to compute magnitude
	magnitude = sqrt(squared);
	
	printf("|%s| = %f\n\n", vectorname, magnitude);
	
	fclose(out);
	return;
}

/*
Function Name: mmultiply()
Author: Andrew Flair
Purpose:

This function takes in the names of two different matrices. It
then tries to find .txt files of the matrices and returns if
there are no such files. It reads the matrices from the files
into variables matrix1 and matrix2. The function detects if the
matrices are not compatible to be multiplied and multiplies them
together if they are. The function prints out the result like so:

r1c1	r1c2	r1c3	...
r2c1	r2c2	r2c3	...
r3c1	r3c2	r3c3	...
...		...		...

The function returns nothing.

*/

void mmultiply(char *name1, char *name2){
	
	char *extension = ".txt";
	char file1[strlen(name1) + strlen(extension) + 1];
	char file2[strlen(name2) + strlen(extension) + 1];
	FILE *input1, *input2;
	int i, j, x, y, row1, col1, row2, col2, sum, a, b, c; // i,j,x,y are matrix sizes, the rest are dummies used in for loops
	float matrix1[33][33], matrix2[33][33], matrix3[33][33]; // matrix3 is the multiplied matrix result
	
	i = j = x = y = sum = 0;
	
	snprintf(file1, sizeof(file1), "%s%s", name1, extension); // Create .txt file based on user input 'name'
	snprintf(file2, sizeof(file2), "%s%s", name2, extension);
	
	input1 = fopen(file1, "r");
	input2 = fopen(file2, "r");
	
	// Check if file exists, if so read it into matrix1
	if(input1 != NULL){
		fscanf(input1, "%d %d", &i, &j);
		for(row1 = 0; row1 < i; row1++){
			for(col1 = 0; col1 < j; col1++){
				fscanf(input1, "%f", &matrix1[row1][col1]);
			}
		}
	}
	else{
		printf("Invalid matrix 1 name.\n\n");
		fclose(input1);
		fclose(input2);
		return;
	}
	
	// Check if file exists, if so read it into matrix2
	if(input2 != NULL){
		fscanf(input2, "%d %d", &x, &y);
		for(row2 = 0; row2 < x; row2++){
			for(col2 = 0; col2 < y; col2++){
				fscanf(input2, "%f", &matrix2[row2][col2]);
			}
		}
	}
	else{
		printf("Invalid matrix 2 name.\n\n");
		fclose(input1);
		fclose(input2);
		return;
	}
	
	// Check if matrices are able to multiply in the order Matrix1 * Matrix2
	if(j != x){
		printf("Matrices are not the correct size or in the correct order to be multiplied.\n\n");
		fclose(input1);
		fclose(input2);
		return;
	}
	// Three nested for loops for the matrix multiplication calculation
	// This calculates the correct multiplication sum and places it into a new matrix 'Matrix3'
	if(j == x){
		for(a = 0; a < i; a++){
			for(b = 0; b < y; b++){
				for(c = 0; c < x; c++){
					sum += matrix1[a][c] * matrix2[c][b];
				}
				
				matrix3[a][b] = sum;
				sum = 0;
			}
		}
	}
	
	
	// Print out newly multiplied matrix using similar for loop
	printf("\nThe product of %s and %s is:\n\n", name1, name2);
	for(a = 0; a < i; a++){
		for(b = 0; b < y; b++){
			printf("%.2f\t", matrix3[a][b]);
		}
		printf("\n");
	}
	printf("\n");
	
	fclose(input1);
	fclose(input2);
			
	return;
}







