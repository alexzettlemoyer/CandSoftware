/**
	@file filebuffer.c
	@author Alex Zettlemoyer
*/

#include "filebuffer.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 3
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

void appendFileBuffer( FileBuffer *buffer, byte val )
{
	if ( (*buffer).length == (*buffer).capacity ) {
		(*buffer).capacity *= RESIZE_FACTOR;
		(*buffer).data = realloc( (*buffer).data, (*buffer).capacity * sizeof(byte) );
	}
		
	(*buffer).data[ (*buffer).length ] = val;
	(*buffer).length++;
}

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
	
	// while ( (fread( (*buffer).data, sizeof( byte ), sizeof( (*buffer).data ), input)) == 3 ) {
//   	}
	
	return buffer;
}

void saveFileBuffer( FileBuffer *buffer, char const *filename )
{
}

int main() 
{
	FileBuffer *buffer = loadFileBuffer("original-03.bin");
	
	printf("capacity %d\n", buffer -> capacity);
	printf("length %d\n", buffer -> length);
	
	for ( int i = 0; i < (*buffer).length; i++ )
		printf(" %d", (*buffer).data[i]);
		
	printf("\n");
	
	freeFileBuffer( buffer );
	return 0;
}