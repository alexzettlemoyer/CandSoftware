/**
	@file io.c
	@author Alex Zettlemoyer
	io has functions to read in a single line of text into a string
	and functions to change the output color to green, yellow, and back to default
*/
#include "io.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
bool readLine( FILE *fp, char str[], int n ) 
{
	// if there's nothing left to read in the file
	if ( !fp ) {
		return false;
	}
	
	int i = 0;
	char ch = ' ';
	
	// keep reading the next character
	while ( fscanf(fp, "%c", &ch) == 1 ) {
		if ( ch == EOF || ch == '\n') {
			break;
		}
		if (i < n) {
			str[i] = ch;
		}
		i++;
	}
	
	// if nothing was read in, nothing is left to read in
	if ( i == 0 ) {
		return false;
	}
	// otherwise there is still input and this input needs a null termination
	else {
		str[i] = '\0';
		return true;
	}
}

/**
	colorGreen
	changes the output color to green
	ANSI code 1B 5B 33 32 6D
*/
void colorGreen()
{
	printf("%c%c%c%c%c", 0x1B, 0x5B, 0x33, 0x32, 0x6D);
}

/**
	colorYellow
	changes the output color to yellow
	ANSI code 1B 5B 33 33 6D
*/
void colorYellow()
{
	printf("%c%c%c%c%c", 0x1B, 0x5B, 0x33, 0x33, 0x6D);
}

/**
	colorDefault
	changes the output color to default (black)
	ANSI code 1B 5B 30 6D
*/
void colorDefault()
{
	printf("%c%c%c%c", 0x1B, 0x5B, 0x30, 0x6D);
}