/**
	@file input.c
	@author Alex Zettlemoyer
*/
#include <stdio.h>
#include <stdlib.h>

/** Initial capacity of the resizable array for input */
#define INITIAL_CAPACITY 5


/**
	readLine
	reads in a line of input of arbitrary length (using a resizable array)
	and a pointer to the heap memory storing the string
	@param fp the File to read from
	@return * a pointer to the string read in
*/
char *readLine(FILE *fp)
{
	int length = 0;
	int size = INITIAL_CAPACITY;
	char *s = (char *) malloc( INITIAL_CAPACITY * sizeof( char ) );
	
	char ch = 'p';
	
	while ( fscanf( fp, "%c", &ch ) == 1 && ch != '\n' && ch != EOF ) {
			
		s[ length ] = ch;
		length++;
		
		// if we filled the entire array, resize
		if ( length == size ) {
			// double the array size
			size *= 2;
			// reallocate it
			s = (char *) realloc( s, size * sizeof( char ));
		}
	}
	
	if ( ch == EOF && length == 0 )
		return NULL;
	
	length++;
	s[ length ]	= '\0';
	
	return s;
}