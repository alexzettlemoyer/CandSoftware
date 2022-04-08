/** 
    @file encode.c
    @author Alex Zettlemoyer
    encode program
    usage: encode [-b] [-p] <input-file> <output-file>
    reads in the input.txt file and encodes the characters
    prints the encoded bytes to the output.bin file
    optional command line arguments -b -p
    -b disables line breaks (normally after 76 characters)
    -p disables padding (extra = character for empty bytes)
*/

#include "state24.h"
#include "filebuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** max number of characters on a line to output */
#define LINE_LIMIT 76
/** number of characters in the buffer */
#define NUM_CHARS 4
/** number of bytes in the state */
#define NUM_BYTES 3

/**
    starts the program
    reads in the inputfile ( second to last command line argument )
    writes the encoded binary text to the output file ( last argument )
    optional -p option to disable padding
    optional -b option to disable line breaks
    @param args the number of command line arguments
    @param argv the argument vector of character array arguments
*/
int main( int args, char *argv[] )
{
    bool padding = true;
    bool lineBreaks = true;
    
    // not enough command line arguments
    if ( args < 3 ) {
        fprintf( stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
        exit( EXIT_FAILURE );
    }
    
    // if option is added, check that first two arguments are -b or -p
    for ( int i = 1; i < args - 2; i++ ) {

        // check for line break and padding disabled option
        if ( strcmp( argv[ i ], "-b") == 0 )
            lineBreaks = false;
        else if ( strcmp( argv[ i ], "-p") == 0 )
            padding = false;
        else {
            fprintf( stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
            exit( EXIT_FAILURE );
        }
    }
        
    char *inputfile = argv[ args - 2 ];
    char *outputfile = argv[ args - 1 ];
    
    // load the inputfile into the file buffer
    FileBuffer *filebuffer = loadFileBuffer( inputfile );
    
    // open the outputfile
    FILE *output = fopen( outputfile, "w");
    if ( !output ) {
        perror( outputfile );
        exit( EXIT_FAILURE );
    }
    
    // initialize the state
    State24 state;
    initState( &state );
    
    int counter = 0;

    // for each byte in the filebuffer
    for ( int i = 0; i < (*filebuffer).length; i++ ) {
    
        // add the byte
        addByte( &state, (*filebuffer).data[i] );
        
        // if the state is full or we're at the last byte in the filebuffer
        if ( state.length == NUM_BYTES || i == (*filebuffer).length - 1 ) {
            char buffer[ NUM_CHARS ];
            int match = getChars( &state, buffer );
            
            // if padding is enabled
            if ( padding ) {
                // fill the empty characters with =
                for ( int i = match; i < NUM_CHARS; i++ ) {
                    buffer[i] = '=';
                }
                match = NUM_CHARS;
            } 
            // for each matched character
            for ( int m = 0; m < match; m++ ) {
                fprintf( output, "%c", buffer[m] );
                counter++;
                
                // if linebreaks are enabled and we're at the limit
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
