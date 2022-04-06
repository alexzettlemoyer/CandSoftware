/**
	@file filebuffer.h
	@author Alex Zettlemoyer
*/

#ifndef _FILEBUFFER_H_
#define _FILEBUFFER_H_

/** A shorthand for talking about a byte. */
typedef unsigned char byte;

/** 
	Representation of a resizable array of bytes, with functions to
    make it easy to read and write the contents of this array to a
    file. 
*/
typedef struct {
  	/** Resizable array of bytes stored in this filebuffer. */
  	byte *data;
	int length;
	int capacity;
	
} FileBuffer;

#endif

FileBuffer *loadFileBuffer( char const *filename );

void freeFileBuffer( FileBuffer *buffer );

void saveFileBuffer( FileBuffer *buffer, char const *filename );
