/** 
	@file encode.c
	@author Alex Zettlemoyer
*/

#include "state24.h"
#include "filebuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LINE_LIMIT 76
#define NUM_CHARS 4
#define NUM_BYTES 3

void usage()
{
	fprintf( stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
	exit( EXIT_FAILURE );
}

int main( int args, char *argv[] )
{
	bool padding = true;
	bool lineBreaks = true;
	
	// not enough command line arguments
	if ( args < 3 ) 
		usage();
	// if option is added, check that first two arguments are -b or -p
	if ( args > 3 && strcmp( argv[1], "-b") != 0 && strcmp( argv[1], "-p") != 0)
			usage();
	if ( args > 4 && strcmp( argv[2], "-b") != 0 && strcmp( argv[2], "-p") != 0)
			usage();
	
	// check for line break and padding disabled option
	if ( strcmp( argv[1], "-b") == 0 || strcmp( argv[2], "-b") == 0)
		lineBreaks = false;
	if ( strcmp( argv[1], "-p") == 0 || strcmp( argv[2], "-p") == 0 )
		padding = false;
		
	char *inputfile = argv[ args - 2 ];
	char *outputfile = argv[ args - 1 ];
	
	FileBuffer *filebuffer = loadFileBuffer( inputfile );
	
	FILE *output = fopen( outputfile, "w");
	if ( !output ) {
		perror( outputfile );
		exit( EXIT_FAILURE );
	}
	
	State24 state;
	initState( &state );
	
	int counter = 0;

	for ( int i = 0; i < (*filebuffer).length; i++ ) {
		addByte( &state, (*filebuffer).data[i] );
		
		
		if ( state.length == NUM_BYTES || i == (*filebuffer).length - 1 ) {
			char buffer[ NUM_CHARS ];
			int match = getChars( &state, buffer );
			
			if ( padding ) {
				for ( int i = match; i < NUM_CHARS; i++ ) {
					buffer[i] = '=';
				}
				match = NUM_CHARS;
			} 
			
			for ( int m = 0; m < match; m++ ) {
				fprintf( output, "%c", buffer[m] );
				counter++;
				
				if ( counter == LINE_LIMIT && lineBreaks ) {
					fprintf( output, "\n");
					counter = 0;
				}
			}
		}
	}
	
	fprintf( output, "\n" );
	fclose( output );
	freeFileBuffer( filebuffer );
	exit( EXIT_SUCCESS );
}