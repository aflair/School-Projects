# School-Projects
A small selection of programming assignments completed during my time at Clemson University.

## prog1.c
This program mimics the game BINGO, in which the user must get 4 squares in a line to win the game. The word BINGO has been replaces with DABO (after Dabo Swinney, head coach of the Clemson Tiger's football team). This program simply asks for the coordinates of the bingo board and uses win detection logic to determine if the user has won. The location of the "free space" is chosen randomly each round. The letters "CU" (for Clemson University) are used to represent a mark on the bingo board.

## prog4.c

This program continuously scans for 1 of 6 commands. The
user can either: create a vector, create a matrix, add
two vectors, find the magnitude of a vector, multiply two
matrices together, or quit the program. Every command is
split up into a function (except quit) and details about
each command can be found in the information above the
function.

### Assumptions:

- Since <math.h> is included one must compile with the -lm tag.
- Only matrices that have been created with this program can be used,
  unless the .txt file has the required metedata in the beginning.
- Vectors and matrices cannot have more than 32 rows or columns
- For the sake of continuity, vector/matrix names cannot exceed 32 characters
- Vectors and matrices must only contain floating point numbers (no text/symbols)

### Commands

create vector (num_cols) (name)

- prompts user for the values to store in the new vector, and stores the vector in name.txt

create matrix (num_rows) (num_cols) (name)

- prompts user for the values to store in the new matrix, and stores the vector in name.txt

add vectors (name1) (name2)

- takes two vectors of equal length and displays a vector with the added values

magnitude (vector_name)

- calculates the magnitude of a given vector

multiply matrices (name1) (name2)

- takes two matrices and (if able) displays a matrix with the multiplied values

quit

- exits the program

## prog5.c

This program takes in the name of a text file containing any
assortment of ASCII characters. The function then gives a menu
for the user containing five options. With the exception of the
5th option (quit), this program breaks each option down into
a different function. The description of each function can be
found in the function header.

File example.txt has been provided to use for an example.

### Assumptions:

- The name of a text file should be given as a parameter when the program is executed
  (ex. "./a.out file.txt")
- Text files contain only ASCII characters
- User has read the function descriptions before executing the program

## prog6.c

The purpose of this program is to take in two command line inputs,
one should be the name of an input 24-bit .bmp file and the second
should be the desired name of an output 24-bit .bmp file. The
program then reads the header information and pixel data of the
input file and applies a filter to the pixels. The filtered image
is stored into a seperate pixel data array and is then written to
a file with the desired output name.

File CU.bmp has been provided to use an example.

### Assumptions:

- The first command line argument is the name of a valid .bmp file in the directory
- The .bmp file is a standard format 24-bit .bmp file
