/**
	@file state24.c
	@author Alex Zettlemoyer
*/
#include "state24.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define CAPACITY 3

void initState( State24 *state )
{
	(*state).data = (byte *) malloc( CAPACITY * sizeof( byte ));
	memset( (*state).data, '\0', CAPACITY * sizeof( byte ));
	(*state).length = 0;
}

bool validChar( char ch )
{
	//  ch is an uppercase letter OR ch is a lowercase letter 
	if ( ('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') 
		// OR ch is a number OR ch is + OR ch is /
		|| ('0' <= ch && ch <= '9') || ch == '+' || ch == '/')
		return true;
	return false;
}

void addByte( State24 *state, byte b )
{
	if ( (*state).length < CAPACITY ) {
		(*state).data[ (*state).length ] = b;
		(*state).length++;
	}
}

void addChar( State24 *state, char ch )
{
	if ( (*state).length < CAPACITY ) {
		(*state).data[ (*state).length ] = ch;
		(*state).length++;
	}
}

int getBytes( State24 *state, byte buffer[] )
{
	
	return 0;
}

int getChars( State24 *state, char buffer[] )
{
	int length = 0;
	byte values[4];
	
	// if the first data byte is not empty
	if ( (*state).data[0] ) {
	
		// get the 6 high-order bits of the first data byte
		values[0] = (*state).data[0] >> 2;
		length++;
		
		// 00110000 where 11 represent the 2 low-order bits from first data byte
		byte lastTwo1 = ((*state).data[0] & 0x03) << 4;
		// get the 4 high-order bits of the second data byte
		byte firstFour2 = (*state).data[1] >> 4;
		// 'concatenate' the two to get the second character value
		values[1] = lastTwo1 ^ firstFour2;
		length++;
	}
	
	// if the second data byte is filled
	if ( (*state).data[1] ) {
	
		// 00111100 where 1111 represent the 4 low-order bits from second data byte
		byte lastFour2 = ((*state).data[1] & 0x0F) << 2;
		// get the 2 high-order bits of the third data byte
		byte firstTwo3 = ((*state).data[2] >> 6);
	
		// 'concatenate' the two to get the third character value
		values[2] = lastFour2 ^ firstTwo3;
		length++;
	}
	
	// if the third data byte is filled
	if ( (*state).data[2] ) {
	
		// get the 6 low-order bits from the third data byte
		values[3] = (*state).data[2] & 0x3F;
		length++;
	}

	for ( int i = 0; i < length; i++ ) {
		
		// the value should be encoded to uppercase letter
		if ( values[i] <= 25 )
			buffer[i] = 'A' + values[i];
		// the value should be encoded to a lowercase letter
		else if ( values[i] <= 51 )
			buffer[i] = 'a' + values[i];
		// the value should be encoded to a number
		else if ( values[i] <= 61 )
			buffer[i] = '0' + values[i];
		// the value should be encoded to +
		else if ( values[i] == 62 )
			buffer[i] = '+';
		// the value should be encoded to /
		else
			buffer[i] = '/';
		
	}
	printf("\n");
	return length;
}

int main()
{
	// Make a new state and initialize it.
	State24 state;
	initState( &state );

	// Put three bytes in the state.
	addByte( &state, 0x34 );
	addByte( &state, 0x24 );
	addByte( &state, 0x94 );
	
	printf("%d %d %d\n", state.data[0], state.data[1], state.data[2]);
	
	char buffer[4];
	int match = getChars( &state, buffer);
	
	printf("%c %c %c %c\n", buffer[0], buffer[1], buffer[2], buffer[3]);
	printf("%d\n", match);
	
	return 0;
}
