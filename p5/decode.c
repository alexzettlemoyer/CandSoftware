/**
	@file decode.c
	@author Alex Zettlemoyer
*/
#include "state24.h"
#include "filebuffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


#define ARG_NUM 3

void invalidFile( FILE *file, FileBuffer *fb )
{
	fprintf( stderr, "Invalid input file\n");
	freeFileBuffer( fb );
	fclose( file );
	exit( EXIT_FAILURE );
}

int main( int args, char *argv[] ) 
{
	
	if ( args != ARG_NUM ) {
		printf( "usage: decode <input-file> <output-file>\n" );
		exit( EXIT_FAILURE );
	}
	
	char *inputfile = argv[ 1 ];
	char *outputfile = argv[ 2 ];
	
	
	FILE *input = fopen( inputfile, "r" );
	if ( !input ) {
		perror( inputfile );
		exit( EXIT_FAILURE );
	}
	
	FileBuffer *filebuffer = makeFileBuffer();
	
	State24 state;
	initState( &state );
	
	
	char ch = '\0';
	//char nextCh = '\0';
	bool equals = false;
	
	while ( fscanf( input, "%c", &ch ) != EOF ) {
			
		if ( validChar(ch) )
			addChar( &state, ch );
		else if ( ch == '=' )
			equals = true; 
		else if ( !isspace( ch ) )
			invalidFile( input, filebuffer );
		
		if ( equals && ch != '=' && !isspace( ch ) )
			invalidFile( input, filebuffer );
								
		if ( state.bitlength == 24 ) {
			byte bytes[ 3 ];
			memset( bytes, '\0', 3 * sizeof( byte ));
			
			int length = getBytes( &state, bytes );
			
			for ( int m = 0; m < length; m++ )
				appendFileBuffer( filebuffer, bytes[ m ]);
		}
	}
	
	if ( state.bitlength > 0 ) {
		byte bytes[ 3 ];
		memset( bytes, '\0', 3 * sizeof( byte ));
			
		int length = getBytes( &state, bytes );
			
		for ( int m = 0; m < length; m++ )
			appendFileBuffer( filebuffer, bytes[ m ]);
	}
	
	saveFileBuffer( filebuffer, outputfile );
	
	freeFileBuffer( filebuffer );
	fclose( input );
	exit( EXIT_SUCCESS );
}