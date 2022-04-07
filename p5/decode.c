/**
	@file decode
	@author Alex Zettlemoyer
*/
#include "state24.h"
#include "filebuffer.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#define NUM_BITS 24
#define NUM_BYTES 3

void invalidFile( FileBuffer *fb )
{
	fprintf( stderr, "Invalid input file\n");
	freeFileBuffer( fb );
	exit( EXIT_FAILURE );
}

int main( int args, char *argv[] )
{
	if ( args != 3 ) {
		printf("usage: decode <input-file> <output-file>\n");
		exit( EXIT_FAILURE );
	}
	
	char *inputfile = argv[ 1 ];
	char *outputfile = argv[ 2 ];
	
	FILE *input = fopen( inputfile, "r");
	
	if ( !input ) {
		perror( inputfile );
		exit( EXIT_FAILURE );
	}
	
	bool equals = false;
	
	FileBuffer *filebuffer = makeFileBuffer();
	
	State24 state;
	initState( &state );
	
	int match;
	byte buffer[ NUM_BYTES ];
	
	char currentChar = ' ';
	while( fscanf( input, "%c", &currentChar ) == 1 && currentChar != EOF ) {
		
		if ( validChar( currentChar ))
			addChar( &state, currentChar );
		else {
			if ( currentChar != '=' && !isspace( currentChar ))
				invalidFile( filebuffer );
			if ( currentChar == '=' )
				equals = true;		
		}
		
		//printf("length %d\n", state.bitlength);
		
		// if an encoding character is following a =
		if ( equals && currentChar != '=' && !isspace( currentChar ))
			invalidFile( filebuffer );
			
		if ( state.bitlength == NUM_BITS ) {
			
			match = getBytes( &state, buffer );
			//printf("%d\n", match);
			
			for ( int m = 0; m < match; m++ )
				appendFileBuffer( filebuffer, buffer[m] );
		}
	}
	
	if ( state.bitlength > 0 ) {
			
		match = getBytes( &state, buffer );
		//printf("%d\n", match);
			
		for ( int m = 0; m < match; m++ )
			appendFileBuffer( filebuffer, buffer[m] );
	}
	saveFileBuffer( filebuffer, outputfile );
		
	freeFileBuffer( filebuffer );
	fclose( input );
	exit( EXIT_SUCCESS );
}