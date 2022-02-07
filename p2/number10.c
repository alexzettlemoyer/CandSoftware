/**
	@file number10.c
	@author Alex Zettlemoyer
*/
#include "number.h"
#include <stdio.h>

/**
	skipSpace
	scans until reaching a non-WhiteSpace character
	non-WhiteSpace includes EOF and \n
	@return the int code for the first non-WhiteSpace character
*/
int skipSpace()
{
	char ch;
	
	while (scanf("%c", &ch) == 1) {
	
		if (ch != ' ') {
			if (ch == EOF) {
				return EOF;
			}
			if (ch == '\n') {
				return '\n';
			}
			return ch;
		}
	}
	return EOF;	
}

/**
	reads in the next value from input
	parses the char to a long integer value
	@return the long int value parsed
*/
long parseValue()
{
	int charVal = skipSpace();
	int numVal;
	long value = 0;
	
	// while the character is a Base 10 number [0-9]
	while (BASE_10_MIN <= charVal && charVal <= BASE_10_MAX) {
		
		numVal = charVal - 48;
		
		// slide all values over one
		value *= 10;
		// add in the new value
		value += numVal;
		
		charVal = skipSpace();
	}
	
	char character = charVal;
	
	// add back the operator read in
	ungetc(character, stdin);
	return value;
}

/**
	prints the value as a long integer
	@param val the value to print
*/
void printValue( long val )
{
	printf("%ld\n", val);
}