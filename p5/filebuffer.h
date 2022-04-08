/**
    @file filebuffer.h
    @author Alex Zettlemoyer
    FileBuffer functionality for binary file input / output
    encode uses loadFileBuffer to load the characters into FileBuffer data array
    decode uses appendFileBuffer to add bytes to the FileBuffer data array
    and saveFileBuffer to print the bytes to a binary file
*/

#ifndef _FILEBUFFER_H_
#define _FILEBUFFER_H_

/** A shorthand for talking about a byte. */
typedef unsigned char byte;

/** 
    Representation of a resizable array of bytes, with functions to
    make it easy to read and write the contents of this array to a file. 
*/
typedef struct {
    /** Resizable array of bytes stored in this filebuffer. */
    byte *data;
    int length;
    int capacity;
    
} FileBuffer;

#endif

/**
    makeFileBuffer
    dynamically allocates a FileBuffer
    initializes the filebuffer to contain an empty sequence of bytes
    @return a pointer to the newly created FileBuffer
*/
FileBuffer *makeFileBuffer();

/**
    freeFileBuffer
    frees the given FileBuffer and its data array
    @param FileBuffer pointer
*/
void freeFileBuffer( FileBuffer *buffer );

/**
    appendFileBuffer
    adds a byte value to the end of the buffers data
    resizes the FileBuffer's data array if necessary
    @param buffer the FileBuffer to add to
    @param val the byte value to append
*/
void appendFileBuffer( FileBuffer *buffer, byte val );

/**
    loadFileBuffer
    creates a new FileBuffer
    loads a sequence of bytes from the given file into the buffers data
    @param filename of the File to read in
    @return a pointer to the new loaded FileBuffer
*/
FileBuffer *loadFileBuffer( char const *filename );

/**
    saveFileBuffer
    prints the data of the FileBuffer to a binary file
    @param buffer the FileBuffer to save
    @param filename of the File to save to
*/
void saveFileBuffer( FileBuffer *buffer, char const *filename );
