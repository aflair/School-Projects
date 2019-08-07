/*

aflair
prog5.c by Andrew Flair
ECE 2220 - Spring 2015
Programming Assignment 5
3/25/15

Purpose:

This program takes in the name of a text file containing any
assortment of ASCII characters. The function then gives a menu
for the user containing five options. With the exception of the
5th option (quit), this program breaks each option down into
a different function. The description of each function can be
found in the function header.


Assumptions:
- The name of a text file should be called when the program is executed
  (ex. "./a.out file.txt")
- Text files contain only ASCII characters

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void csearch(int size, char *buffer);

void cdisplay(int size, char *buffer);

void ssearch(int size, char *buffer);

void sumdisplay(int size, char *buffer);

int main(int argc, char *argv[]){
	FILE *file;
	char *buffer;
	char select;
	int i, j, size;
	
	file = fopen(argv[1], "r");

	/* Check to see if file name exists in directory */
	if(file == NULL){
		printf("File does not exist.\n"); return -1;
	}
	
	/* Uses ftell and fseek to determine the size of the file */
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	
	/* Allocate memory for buffer based on size of file */
	buffer = (char*) calloc(size+1, sizeof(char));
	j = 0;
	
	/* Use fgetc to read characters one by one into buffer from file */
	while((i = fgetc(file)) != EOF){
		buffer[j] = i;
		j++;
	}
	

	/* While loop until user decides to quit */
	j = 0;
	while(j != 1){
		printf("\nEnter a number to select a menu option:\n");
		printf("1) Character Search\t2) Character Display\n");
		printf("3) String Search\t4) Character Sum\n");
		printf("5) Quit\n");
		
		scanf(" %c", &select);
		if(select == '5'){
			printf("\nQuiting program.\n"); break;
		}
		else if(select == '1'){
			csearch(size, buffer);
		}
		else if(select == '2'){
			cdisplay(size, buffer);
		}
		else if(select == '3'){
			ssearch(size, buffer);
		}
		else if(select == '4'){
			sumdisplay(size, buffer);
		}
		else{
			printf("Incorrect menu option.\n");
		}
	}

	
	free(buffer);
	fclose(file);
	return 0;
}

/*
Function Name: csearch()
Author: Andrew Flair
Purpose:

This function takes the size and ptr of a buffer that was
created from the text file that the user inputted. It then
prompts the user to input a character to be searched. The 
function will determine if input is decimal or hex and search
the buffer accordingly. It will then display in a neat table of
each occurance of the character in the text file in blocks of
16 bytes. The function returns nothing.

*/

void csearch(int size, char *buffer){
	char input[5];
	char output;
	int number, i, j, k, addmod, adds[100], ints[100];
	char instance[10];
	printf("Enter a decimial(0-255) or hexadecimal(0x00-0xFF) value to be searched: ");
	scanf(" %s", input);
	
	/* Determine whether input is hex or dec and store into number */
	if((input[0] == '0') && (input[1] == 'x')){
		number = (int) strtol(input, NULL, 16);
	}
	else{
		number = (int) strtol(input, NULL, 10);
	}
	if((number < 0) || (number > 255)){
		printf("Invalid input.\n");
		return;
	}
	
	sprintf(&output,"%c", number); // print the character to an actual char variable (output)
	
	for(i = 0; i < 100; i++) adds[i] = 0, ints[i] = -1;
	
	/* for loop that searches buffer for requested character and adds the address to adds[] */
	j=0;
	for(i = 0; i < size; i++){
		if(buffer[i] == output){
			sprintf(instance, "%lld", (long long int)&buffer[i]);
			adds[j] = atoi(instance);
			ints[j] = i;
			j++;
		}
	}
	
	/* If character doesn't occur at all in file tell and exit */
	if(adds[0] == 0){
		printf("\nNone found.\n");
		return;
	}
	
	/* While loop that prints the occurances in a table for each one*/
	i=0;
	while(adds[i] != 0){
		j = adds[i] % 16;
		addmod = adds[i] - j;
		printf("\t\t0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5\n");
		printf("[%d] [\t", addmod);
		for(k = 0; k < 16; k++){
			if(buffer[ints[i]-j+k] != '\n') printf("%c  ", buffer[ints[i]-j+k]);
			else printf("   ");
		}
		printf("]\n\t\t");
		for(k = 0; k < 16; k++){
			if(buffer[ints[i]-j+k] != '\n') printf("%x ", buffer[ints[i]-j+k]);
			else printf("10 ");
		}
		printf("\n\t\t");
		for(k = 0; k < j; k++) printf("   ");
		printf("^\n\n");
		i++;
	}	
	return;
}

/*
Function Name: cdisplay()
Author: Andrew Flair
Purpose:

This function takes the size and ptr of a buffer that was
created from the text file that the user inputted. The function
then tells the user the range of displays to use. It then
prompts for a correct address input and displays in the
same table as csearch() the character that is located at the
address specified. This function returns nothing.

*/

void cdisplay(int size, char *buffer){
	char instance[10];
	int add1, add2, addmod, input, i, j, k;
	
	/* finds the start and end of the addresses */
	sprintf(instance, "%lld", (long long int)&buffer[0]);
	add1 = atoi(instance);
	sprintf(instance, "%lld", (long long int)&buffer[size]);
	add2 = atoi(instance);
	
	/* Tell user range of addresses and prompt for correct input */
	printf("The adresses range from %d - %d\n", add1, add2);
	printf("Enter address: "); scanf(" %d", &input);
	while((input > add2) || (input < add1)){
		printf("Incorrect input, try again: ");
		scanf(" %d", &input);
	}
	
	/* Search buffer for the position of the address --> i */
	for(i = 0; i < size; i++){
		sprintf(instance, "%lld", (long long int)&buffer[i]);
		k = atoi(instance);
		if(input == k){
			break;
		}
	}
	
	/* find start address closest block of 16 bytes to the input  */ 
	j = input % 16;
	addmod = input - j;
	
	
	/* Print the table using same method as previous function */
	printf("\t\t0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5\n");
	printf("[%d] [\t", addmod);
	for(k = 0; k < 16; k++){
		if(buffer[i-j+k] != '\n') printf("%c  ", buffer[i-j+k]);
		else printf("   ");
	}
	printf("]\n\t\t");
	for(k = 0; k < 16; k++){
		if(buffer[i-j+k] != '\n') printf("%x ", buffer[i-j+k]);
		else printf("10 ");
	}
	printf("\n\t\t");
	for(k = 0; k < j; k++) printf("   ");
	printf("^\n\n");
	i++;
	
	return;
}

/*
Function Name: ssearch()
Author: Andrew Flair
Purpose:

This function takes the size and ptr of a buffer that was
created from the text file that the user inputted. The
function then prompts the user to input a string to be
searched for inside of the buffer. The function will print
the same table as csearch() each occurance of the string.
If the string is located in more than 1 block of 16 bytes
then the function will display them both. This function
returns nothing. 

*/

void ssearch(int size, char *buffer){
	char input[32];
	int i, j, k;
	int instances[100];
	int adds[100];
	char instance[10];
	int addmod;
	
	for(i = 0; i < 100; i++) instances[i] = -1; // Initialize values
	
	printf("Input a string to be searched: ");
	scanf(" %s", input);
	
	
	/* Scan buffer to find every instance of occurrance */
	i = 0;	
	j = strlen(input);
	k = 0;
	while(i < size){		
		if(strncmp(&buffer[i], input, j) == 0){
			instances[k] = i;
			k++; 
		}
		i++;
	}
	
	/* record addresses of each occurance into 'adds[]' */
	for(i = 0; i < 100; i++){
		if(instances[i] != -1){
			sprintf(instance, "%lld", (long long int)&buffer[instances[i]]);
			adds[i] = atoi(instance);
		}
	}
	
	/* while loop to print each instance of search result */
	i = 0;
	while(instances[i] != -1){
		j = adds[i] % 16;
		addmod = adds[i] - j;
		printf("\t\t0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5\n");
		printf("[%d] [\t", addmod);
		for(k = 0; k < 16; k++){
			if(buffer[instances[i]-j+k] != '\n') printf("%c  ", buffer[instances[i]-j+k]);
			else printf("   ");
		}
		printf("]\n\t\t");
		for(k = 0; k < 16; k++){
			if(buffer[instances[i]-j+k] != '\n') printf("%x ", buffer[instances[i]-j+k]);
			else printf("10 ");
		}
		printf("\n\t\t");
		for(k = 0; k < j; k++) printf("   ");
		printf("^\n\n");
		
		/* if string continues beyond a block of 16 bytes print the next block as well */
		if(j + strlen(input) > 16){
			printf("\t\t0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5\n");
			printf("[%d] [\t", addmod+16);
			for(k = 0; k < 16; k++){
				if(buffer[instances[i]-j+k+16] != '\n') printf("%c  ", buffer[instances[i]-j+k+16]);
				else printf("   ");
			}
			printf("]\n\t\t");
			for(k = 0; k < 16; k++){
				if(buffer[instances[i]-j+k+16] != '\n') printf("%x ", buffer[instances[i]-j+k+16]);
				else printf("10 ");
			}
			printf("\n\n\n");			
		}
		i++;		
	}
	
	
	return;
}

/*
Function Name: sumdisplay()
Author: Andrew Flair
Purpose:

This function takes the size and ptr of a buffer that was
created from the text file that the user inputted. The
function then tells the user the range of correct addresses.
It then prompts the user for a correct range of addresses
and sums the values between them. It is displayed as a hex
value. The function returns nothing.

*/

void sumdisplay(int size, char *buffer){
	int add1, add2, input1, input2, i, j, k, result;
	char instance[10];
	
	/* finds the start and end of the addresses */
	sprintf(instance, "%lld", (long long int)&buffer[0]);
	add1 = atoi(instance);
	sprintf(instance, "%lld", (long long int)&buffer[size]);
	add2 = atoi(instance);
	
	/* Tell user range of addresses and prompt for correct input */
	printf("The adresses range from %d - %d\n", add1, add2);
	printf("Enter address 1: "); scanf(" %d", &input1);
	while((input1 > add2) || (input1 < add1)){
		printf("Incorrect input, try again: ");
		scanf(" %d", &input1);
	}
	printf("Enter address 2: "); scanf(" %d", &input2);
	while((input2 > add2) || (input2 < add1) || (input2 < input1)){
		printf("Incorrect input, try again: ");
		scanf(" %d", &input2);
	}
	
	/* find the place in the buffer where the addresses specify */
	for(i = 0; i < size; i++){
		sprintf(instance, "%lld", (long long int)&buffer[i]);
		k = atoi(instance);
		if(input1 == k){
			break;
		}
	}
	for(j = 0; j < size; j++){
		sprintf(instance, "%lld", (long long int)&buffer[j]);
		k = atoi(instance);
		if(input2 == k){
			break;
		}
	}
	
	/* Sum all values in buffer from start address to end and display */
	result = 0;
	for(k = i; k <= j; k++){
		result += buffer[k];		
	}

	printf("The hexidecimal sum from address %d - %d is:\n%x\n", input1, input2, result);
	
	return;
}




