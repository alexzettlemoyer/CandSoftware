/** 
    @file text.c
    @author Alex Zettlemoyer
    Implementation of the Text VType.
*/

#include "text.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** Initial capacity of the resizable array for text's string */
#define INITIAL_CAPACITY 5
/** Factor by to resize string array */
#define RESIZE_FACTOR 2

// print method for Text
static void print( struct VTypeStruct const *v )
{
    // Convert the VType pointer to a Text type
    Text const *this = (Text const *) v;
    
    bool escape = false;
    int length = strlen( this -> str );
    
    for ( int i = 0; i < length; i++ ) {
    
        // if the character is a backslash, the next character will be escaped
        if ( this -> str[ i ] == '\\' && !escape) 
            escape = true;
        else if ( escape ) {
            switch( this -> str[ i ] ) {
                case 'n':
                    printf("\n");
                    break;
                case 't':
                    printf("\t");
                    break;
                case '\\':
                    printf("\\");
                    break;
                case '\"':
                    printf("\"");
                    break;
                default:
                    printf("\%c", this -> str[ i ]);
                    break;
            }
            escape = false;
        }
        else 
            printf("%c", this -> str[ i ]);
    }
}

// equals method for Text
static bool equals( struct VTypeStruct const *a, struct VTypeStruct const *b )
{
    // Make sure the b object is also an Text.
    if ( b -> print != print )
        return false;

    // Compare the val fields inside a and b.
    Text const *this = ( Text const *) a;
    Text const *other = ( Text const *) b;

    return strcmp( this -> str, other -> str) == 0;
}

// hash method for Text
static unsigned int hash( struct VTypeStruct const *b )
{
    Text const *this = ( Text const *) b;
    // start at 1 to skip over first quote
    int i = 1;
    unsigned int hash = 0;
    
    char *value = this -> str;
    
    // end at length - 1 to skip last quote
    while ( i != this -> length - 1) {
        hash += value [ i++ ];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

// destroy method for Text
static void destroy( struct VTypeStruct *v )
{
    Text const *this = ( Text const *) v;
    free( this -> str );
    free( v );
}

// parse method, creates a new VType storing a String
VType *parseText( char const *init, int *n )
{
    // tracks number of characters read
    int len = 0;
    int count = 0;
    int size = INITIAL_CAPACITY;
    char ch = NULL;
        
    if ( sscanf( init, "%c", &ch) != 1 )
        return NULL;
    
    Text *this = (Text *) malloc( sizeof( Text ) );
    this -> str = (char *) malloc( INITIAL_CAPACITY * sizeof(char));
    
    bool quote = false;
    bool escape = false;
    
    // while the character isn't null
    while ( sscanf( init + len, "%c", &ch) == 1 && ch != '\0') {
    
        // if we filled the entire array, resize
        if ( count == size ) {
            // double the array size
            size *= RESIZE_FACTOR;
            // reallocate it
            this -> str = (char *) realloc( this -> str, size * sizeof( char *));
        }
    
        // if it's a backslash the next character will be escaped
        if ( ch == '\\' )
            escape = true;
        // if it's the second quote and the previous character wasn't an escape
        if ( !escape && ch == '\"' && quote ) {
            this -> str [ count++ ] = ch;
            len++;
            break;
        }
        // if it's the first quote
        else if ( ch == '\"' && !quote )
            quote = true;
        
        if ( quote )
            this -> str [ count++ ] = ch;
        len++;
    }
    this -> str[ count ] = '\0';
    
    // Fill in the end pointer, if the caller asked for it.
    if ( n )
        *n = len;
  
    // Allocate a Text struct on the heap and fill in its fields.
    this -> length = count;
    this -> print = print;
    this -> equals = equals;
    this -> hash = hash;
    this -> destroy = destroy;

    // Return it as a pointer to the superclass.
    return (VType *) this;
}
