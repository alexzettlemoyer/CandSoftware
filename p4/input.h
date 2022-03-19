/**
	@file input.h
	@author Alex Zettlemoyer
	header for input.c file
	input handling for agency.c program
*/
#include <stdio.h>

/**
	readLine
	reads in a line of input of arbitrary length (using a resizable array)
	and a pointer to the heap memory storing the string
	@param fp the File to read from
	@return * a pointer to the string read in
*/
char *readLine(FILE *fp);