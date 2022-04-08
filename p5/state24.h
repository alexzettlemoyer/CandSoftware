/**
	@file state24.h
	@author Alex Zettlemoyer
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

void initState( State24 *state );

bool validChar( char ch );

void addByte( State24 *state, byte b );

void addChar( State24 *state, char ch );

int getBytes( State24 *state, byte buffer[] );

int getChars( State24 *state, char buffer[] );