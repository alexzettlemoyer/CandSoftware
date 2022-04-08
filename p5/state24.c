/**
    @file state24.h
    @author Alex Zettlemoyer
    state24 manages the 24 bits that are encoded/decoded at a time ( 3 bytes )
    handles the bitwise operations that encode/decode
    encode uses functions addByte and getChars to encode
    decode uses functions addChar and getBytes to encode
 */
#include "state24.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/** size of a byte */
#define BYTE_SIZE 8
/** size of an encoding character */
#define ENCODING_SIZE 6
/** number of bits in a full state */
#define FULL_STATE 24
/** number of characters */
#define NUM_CHARS 4

/** max value of an uppercase encoding character */
#define UPPERCASE_MAX 26
/** max value of a lowercase encoding character */
#define LOWERCASE_MAX 52
/** max value of a digit encoding character */
#define DIGIT_MAX 62

/** shift by 2 */
#define SHIFT2 2
/** shift by 4 */
#define SHIFT4 4
/** shift by 6 */
#define SHIFT6 6

/** clear mask the high order two bits: 0011 1111 */
#define CLEAR_HIGH_2 0x3F
/** clear mask the high order four bits: 0000 1111 */
#define CLEAR_HIGH_4 0x0F
/** clear mask the high order 6 bits: 0000 0011 */
#define CLEAR_HIGH_6 0x03

/**
    initState
    initializes the state to an empty data array with room for 3 bytes ( 24 bits )
    sets the state's length and bit length to 0
    @param pointer to the state to initialize
*/
void initState( State24 *state )
{
    memset( (*state).data, '\0', CAPACITY * sizeof( byte ));
    (*state).length = 0;
    (*state).bitlength = 0;
}

/**
    validChar
    checks if the given char is a valid encoding character or not
    valid encoding characters are A-Z, a-z, 0-9, +, and /
    @param the char to check for valid
    @return true if a valid encoding character, false otherwise
*/
bool validChar( char ch )
{
    //  ch is an uppercase letter OR ch is a lowercase letter 
    if ( ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') 
        // OR ch is a number OR ch is + OR ch is /
        || ('0' <= ch && ch <= '9') || ch == '+' || ch == '/')
        return true;
    return false;
}

/**
    addByte
    adds the given byte to the next array position in the state's data array
    behavior is undefined if the state is full
    @param state to add the byte to
    @param byte to add to the state
*/
void addByte( State24 *state, byte b )
{
    if ( (*state).length < CAPACITY ) {
        (*state).data[ (*state).length ] = b;
        (*state).length++;
        (*state).bitlength += BYTE_SIZE;
    }
}

/**
    addChar
    adds the given character to the state's data array of bytes
    finds the 6 bit value of the encoded character
    adds the 6 bits according to how many bits are currently in the data array
    behavior is undefined if the state is full or not a valid encoding character
    @param state to add the character to
    @param character to add to the state
*/
void addChar( State24 *state, char ch )
{
    byte value;
    
    // if ch is a capital letter
    if ( 'A' <= ch && ch <= 'Z' )
        value = ch - 'A';
    // if ch is a lowercase letter
    else if ( 'a' <= ch && ch <= 'z' )
        value = ch - 'a' + UPPERCASE_MAX;
    // if ch is a number
    else if ( '0' <= ch && ch <= '9')
        value = ch - '0' + LOWERCASE_MAX;
    // if ch is a +
    else if ( ch == '+' )
        value = DIGIT_MAX;
    // if ch is a  /
    else
        value = DIGIT_MAX + 1;
    
    
    // if the first byte in data is empty
    if ( (*state).bitlength < ENCODING_SIZE )
        (*state).data[ 0 ] = value << SHIFT2;
        
    // if the second byte in data is empty
    else if ( (*state).bitlength < ENCODING_SIZE * 2 ) {

        // append the 2 high-order bits of value to the first byte
        (*state).data[ 0 ] = (*state).data[ 0 ] ^ ( value >> SHIFT4 );
        // set the 4 low-order bits of value to the 4 high-order bits of the second byte
        (*state).data[ 1 ] = value << SHIFT4;
    }
    
    // if the third byte in data is empty
    else if ( (*state).bitlength < ENCODING_SIZE * 3 ){
            
        // append the 4 high-order bits of value to the second byte
        (*state).data[ 1 ] = (*state).data[ 1 ] ^ ( value >> SHIFT2 );

        // set the 2 low-order bits of value to the 2 high-order bits of the third byte
        (*state).data[ 2 ] = value << SHIFT6;
    }
    
    // filling in the last 6 bits of the total 24 bytes
    else
        (*state).data[ 2 ] = (*state).data[2] ^ ( value & CLEAR_HIGH_2 );
    
    (*state).bitlength += ENCODING_SIZE;
    (*state).length++;
}

/**
    getBytes
    fills the given buffer array with current contents of the state
    resets the state to empty
    @param state to get the bytes from
    @param buffer an array of bytes to put the bytes in
    @return length the number of bytes put in the buffer array
*/
int getBytes( State24 *state, byte buffer[] )
{
    int length = (*state).bitlength / BYTE_SIZE;
    
    for ( int i = 0; i < length; i++ ) {
    
        // if the contents aren't null
        if ( (*state).data[i] )
            buffer[i] = (*state).data[i];
    }
    
    memset( (*state).data, '\0', CAPACITY * sizeof( byte ));
    (*state).length = 0;
    (*state).bitlength = 0;
    return length;
}

/**
    getChars
    encodes the bytes in the state to characters
    fills the given buffer array with the encoded characters
    resets state to empty
    @param state to get the chars from
    @param buffer an array of chars to put the characters in
    @return length the number of characters put in the array
*/
int getChars( State24 *state, char buffer[] )
{
    int length = 0;
    byte values[ NUM_CHARS ];
    
    // if the first data byte is not empty
    if ( (*state).bitlength >= BYTE_SIZE ) {
    
        // get the 6 high-order bits of the first data byte
        values[ 0 ] = (*state).data[0] >> SHIFT2;
        length++;
        
        // 00110000 where 11 represent the 2 low-order bits from first data byte
        byte lastTwo1 = ((*state).data[0] & CLEAR_HIGH_6) << SHIFT4;
        // get the 4 high-order bits of the second data byte
        byte firstFour2 = (*state).data[1] >> SHIFT4;
        // 'concatenate' the two to get the second character value
        values[ 1 ] = lastTwo1 ^ firstFour2;
        length++;
    }
    
    // if the second data byte is filled
    if ( (*state).bitlength >= BYTE_SIZE * 2 ) {

        // 00111100 where 1111 represent the 4 low-order bits from second data byte
        byte lastFour2 = ((*state).data[1] & CLEAR_HIGH_4) << SHIFT2;
        // get the 2 high-order bits of the third data byte
        byte firstTwo3 = ((*state).data[2] >> SHIFT6);
    
        // 'concatenate' the two to get the third character value
        values[ 2 ] = lastFour2 ^ firstTwo3;
        length++;
    }
    
    // if the third data byte is filled
    if ( (*state).bitlength == FULL_STATE ) {
    
        // get the 6 low-order bits from the third data byte
        values[ 3 ] = (*state).data[ 2 ] & CLEAR_HIGH_2;
        length++;
    }
    
    // encode all the values as characters in the buffer array
    for ( int i = 0; i < length; i++ ) {
            
        // the value should be encoded to uppercase letter
        if ( values[i] < UPPERCASE_MAX )
            buffer[i] = 'A' + values[i];
        // the value should be encoded to a lowercase letter
        else if ( values[i] < LOWERCASE_MAX )
            buffer[i] = 'a' + values[i] - UPPERCASE_MAX;
        // the value should be encoded to a number
        else if ( values[i] < DIGIT_MAX )
            buffer[i] = '0' + values[i] - LOWERCASE_MAX;
        // the value should be encoded to +
        else if ( values[i] == DIGIT_MAX )
            buffer[i] = '+';
        // the value should be encoded to /
        else
            buffer[i] = '/';
    }
    
    // reset the state to empty
    memset( (*state).data, '\0', CAPACITY * sizeof( byte ));
    (*state).length = 0;
    (*state).bitlength = 0;
    return length;
}
