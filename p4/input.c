/**
    @file input.c
    @author Alex Zettlemoyer
    Input.c handles reading from a file for agency.c
    Reads in one line at a time and stores it in heap memory with a resizable array
*/
#include "input.h"

#include <stdio.h>
#include <stdlib.h>

/** Initial capacity of the resizable array for input */
#define INITIAL_CAPACITY 5
/** Factor by to resize array */
#define RESIZE_FACTOR 2

/**
    readLine
    reads in a line of input of arbitrary length (using a resizable array)
    and a pointer to heap memory storing the string
    @param fp the File to read from
    @return * a pointer to the string read in
*/
char *readLine(FILE *fp)
{
    int length = 0;
    int size = INITIAL_CAPACITY;
    char *s = (char *) malloc( INITIAL_CAPACITY * sizeof( char ) );
    
    char ch = ' ';
    
    // while we haven't reached newline or EOF
    while ( (ch = fgetc( fp )) && ch != '\n' && ch != EOF ) {
        
        //printf("%c ", ch);
            
        s[ length ] = ch;
        length++;
        
        // if we filled the entire array, resize
        if ( length == size ) {
            // double the array size
            size *= RESIZE_FACTOR;
            // reallocate it
            s = (char *) realloc( s, size * sizeof( char *));
        }
    }
    
    // if we didn't read anything in
    if ( ch == EOF && length == 0 ) {
        free( s );
        return NULL;
    }
    
    // add null terminator
    s[ length ] = '\0';
    
    return s;
}