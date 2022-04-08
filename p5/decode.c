/**
	@file decode.c
	@author Alex Zettlemoyer
	decode program
	usage: decode <input-file> <output-file>
	reads in the input.bin file and decodes the characters
	prints the decoded characters to the output.txt file
*/
#include "state24.h"
#include "filebuffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/** expected number of command line arguments */
#define ARG_NUM 3
/** filled state bit length */
#define BITLENGTH 24
/** number of bytes in the buffer array */
#define NUM_BYTES 3

/**
	invalidFile
	prints the invalid file message to standard error
	closes the given file and frees the given filebuffer
	exits the program unsuccessfully
	@param file to close
	@param filebuffer to free
*/
void invalidFile( FILE *file, FileBuffer *fb )
{
	fprintf( stderr, "Invalid input file\n");
	freeFileBuffer( fb );
	fclose( file );
	exit( EXIT_FAILURE );
}

/**
	starts the program
	reads in the input.bin file and decodes the characters
	prints the decoded characters to the output.txt file
    @param args the number of command line arguments
    @param argv the argument vector of character array arguments
*/
int main( int args, char *argv[] ) 
{
	
	if ( args != ARG_NUM ) {
		printf( "usage: decode <input-file> <output-file>\n" );
		exit( EXIT_FAILURE );
	}
	
	char *inputfile = argv[ 1 ];
	char *outputfile = argv[ 2 ];
	
	// open the input file
	FILE *input = fopen( inputfile, "r" );
	if ( !input ) {
		perror( inputfile );
		exit( EXIT_FAILURE );
	}
	
	// initialize the filebuffer
	FileBuffer *filebuffer = makeFileBuffer();
	
	// initialize the state
	State24 state;
	initState( &state );
	
	char ch = '\0';
	bool equals = false;
	
	// while there's more input
	while ( fscanf( input, "%c", &ch ) != EOF ) {
			
		// if the character is a valid encoding character
		if ( validChar(ch) )
			addChar( &state, ch );
		// if the character is an equals
		else if ( ch == '=' )
			equals = true; 
		// if the character isn't valid, isn't =, and isn't space
		else if ( !isspace( ch ) )
			invalidFile( input, filebuffer );
		
		// if the character is after an = and isn't an =
		if ( equals && ch != '=' && !isspace( ch ) )
			invalidFile( input, filebuffer );
		
		// if the state is full						
		if ( state.bitlength == BITLENGTH ) {
			byte bytes[ NUM_BYTES ];
			memset( bytes, '\0', NUM_BYTES * sizeof( byte ));
			
			// get the bytes
			int length = getBytes( &state, bytes );
			
			// add the bytes to the file buffer
			for ( int m = 0; m < length; m++ )
				appendFileBuffer( filebuffer, bytes[ m ]);
		}
	}
	
	// if there's leftover bytes in the state
	if ( state.bitlength > 0 ) {
		byte bytes[ NUM_BYTES ];
		memset( bytes, '\0', NUM_BYTES * sizeof( byte ));
			
		int length = getBytes( &state, bytes );
		
		// add the bytes to the file buffer 
		for ( int m = 0; m < length; m++ )
			appendFileBuffer( filebuffer, bytes[ m ]);
	}
	
	// save the file buffer to the output file
	saveFileBuffer( filebuffer, outputfile );
	
	freeFileBuffer( filebuffer );
	fclose( input );
	exit( EXIT_SUCCESS );
}
