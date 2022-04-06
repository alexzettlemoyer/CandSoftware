/**
	@file filebuffer.c
	@author Alex Zettlemoyer
*/

#include "filebuffer.h"
#include <stdio.h>
#include <stdlib.h>

/** initial Capacity of the buffer array */
#define INITIAL_CAPACITY 3
/** resize factor for reallocating the buffer array */
#define RESIZE_FACTOR 2

/**
	makeFileBuffer
	dynamically allocates a FileBuffer
	initializes the filebuffer to contain an empty sequence of bytes
	@return a pointer to the newly created FileBuffer
*/
FileBuffer *makeFileBuffer() 
{
	FileBuffer *buffer = (FileBuffer *) malloc( sizeof(FileBuffer) );
	(*buffer).data = (byte *) malloc(  INITIAL_CAPACITY * sizeof(byte) );
	
	(*buffer).length = 0;
	(*buffer).capacity = INITIAL_CAPACITY;
	
	return buffer;
}

/**
	freeFileBuffer
	frees the given FileBuffer and its data array
	@param FileBuffer pointer
*/
void freeFileBuffer( FileBuffer *buffer )
{
	free( (*buffer).data );
	free( buffer );
}

/**
	appendFileBuffer
	adds a byte value to the end of the buffers data
	resizes the FileBuffer's data array if necessary
	@param buffer the FileBuffer to add to
	@param val the byte value to append
*/
void appendFileBuffer( FileBuffer *buffer, byte val )
{
	if ( (*buffer).length == (*buffer).capacity ) {
		(*buffer).capacity *= RESIZE_FACTOR;
		(*buffer).data = realloc( (*buffer).data, (*buffer).capacity * sizeof(byte) );
	}
		
	(*buffer).data[ (*buffer).length ] = val;
	(*buffer).length++;
}

/**
	loadFileBuffer
	creates a new FileBuffer
	loads a sequence of bytes from the given file into the buffers data
	@param filename of the File to read in
	@return a pointer to the new loaded FileBuffer
*/
FileBuffer *loadFileBuffer( char const *filename )
{
	FILE *input = fopen( filename, "rb" );
	
	// error opening the input file
	if ( !input ) {
		perror( filename );
		exit( EXIT_FAILURE );
	}
		
	FileBuffer *buffer = makeFileBuffer();
	byte b;
	
	while ( fscanf( input, "%c", &b) == 1 && b != EOF) {
		appendFileBuffer( buffer, b );
	}
	
	fclose( input );
	return buffer;
}

/**
	saveFileBuffer
	prints the data of the FileBuffer to a binary file
	@param buffer the FileBuffer to save
	@param filename of the File to save to
*/
void saveFileBuffer( FileBuffer *buffer, char const *filename )
{
	FILE *output = fopen( filename, "wb" );
	
	if ( !output ) {
		perror( filename );
		freeFileBuffer( buffer );
		exit( EXIT_FAILURE );
	}
	
	//fwrite( buffer, 1, (*buffer).length, output);
	
	for ( int i = 0; i < (*buffer).length; i++ ) {
		fprintf( output, "%c", (*buffer).data[i] );
	}
	
	fclose( output );
}
