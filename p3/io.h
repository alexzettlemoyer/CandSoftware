#include <stdbool.h>
#include <stdio.h>

/**
	readLine
	reads in a line of text from the given file
	stores the line up to n characters in the given character array str
	marks the end of the string with a null terminator
	@param fp a pointer to the file to read from
	@param str a character array to store the next line of chars in
	@param n the number of characters in the line to read
	@return true if there is still remaining input to read, false otherwise
*/
bool readLine( FILE *fp, char str[], int n );

/**
	colorGreen
	changes the output color to green
	ANSI code 1B 5B 33 32 6D
*/
void colorGreen();

/**
	colorYellow
	changes the output color to yellow
	ANSI code 1B 5B 33 33 6D
*/
void colorYellow();

/**
	colorDefault
	changes the output color to default (black)
	ANSI code 1B 5B 30 6D
*/
void colorDefault();