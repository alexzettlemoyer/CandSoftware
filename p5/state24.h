/**
    @file state24.h
    @author Alex Zettlemoyer
    state24 manages the 24 bits that are encoded/decoded at a time ( 3 bytes )
    handles the bitwise operations that encode/decode
    encode uses functions addByte and getChars to encode
    decode uses functions addChar and getBytes to encode
 */

#ifndef _STATE64_H_
#define _STATE64_H_

#include <stdbool.h>

// Include filebuffer to get the byte type.
#include "filebuffer.h"

/** capacity of the State24 data array of bytes = 24 bits */
#define CAPACITY 3

typedef struct {

    byte data[ CAPACITY ];
    int length;
    int bitlength;

} State24;

#endif

/**
    initState
    initializes the state to an empty data array with room for 3 bytes ( 24 bits )
    sets the state's length and bit length to 0
    @param pointer to the state to initialize
*/
void initState( State24 *state );

/**
    validChar
    checks if the given char is a valid encoding character or not
    valid encoding characters are A-Z, a-z, 0-9, +, and /
    @param the char to check for valid
    @return true if a valid encoding character, false otherwise
*/
bool validChar( char ch );

/**
    addByte
    adds the given byte to the next array position in the state's data array
    behavior is undefined if the state is full
    @param state to add the byte to
    @param byte to add to the state
*/
void addByte( State24 *state, byte b );

/**
    addChar
    adds the given character to the state's data array of bytes
    finds the 6 bit value of the encoded character
    adds the 6 bits according to how many bits are currently in the data array
    behavior is undefined if the state is full or not a valid encoding character
    @param state to add the character to
    @param character to add to the state
*/
void addChar( State24 *state, char ch );

/**
    getBytes
    fills the given buffer array with current contents of the state
    resets the state to empty
    @param state to get the bytes from
    @param buffer an array of bytes to put the bytes in
    @return length the number of bytes put in the buffer array
*/
int getBytes( State24 *state, byte buffer[] );

/**
    getChars
    encodes the bytes in the state to characters
    fills the given buffer array with the encoded characters
    resets state to empty
    @param state to get the chars from
    @param buffer an array of chars to put the characters in
    @return length the number of characters put in the array
*/
int getChars( State24 *state, char buffer[] );
