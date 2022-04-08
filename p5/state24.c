/**
	@file state24.c
	@author Alex Zettlemoyer
*/
#include "state24.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BYTE_SIZE 8

void initState( State24 *state )
{
	memset( (*state).data, '\0', CAPACITY * sizeof( byte ));
	(*state).length = 0;
	(*state).bitlength = 0;
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
		(*state).bitlength += BYTE_SIZE;
	}
}

void addChar( State24 *state, char ch )
{
	byte value;
	
	// if ch is a capital letter
	if ( 'A' <= ch && ch <= 'Z' )
		value = ch - 'A';
	// if ch is a lowercase letter
	else if ( 'a' <= ch && ch <= 'z' )
		value = ch - 'a' + 0x1A;
	// if ch is a number
	else if ( '0' <= ch && ch <= '9')
		value = ch - '0' + 0x34;
	// if ch is a +
	else if ( ch == '+' )
		value = 0x3E;
	// if ch is a  /
	else
		value = 0x3F;
	
	
	// if the first byte in data is empty
	if ( (*state).bitlength < 6 )
		(*state).data[0] = value << 2;
		
	// if the second byte in data is empty
	else if ( (*state).bitlength < 12) {

		// append the 2 high-order bits of value to the first byte
		(*state).data[0] = (*state).data[0] ^ ( value >> 4 );
		// set the 4 low-order bits of value to the 4 high-order bits of the second byte
		(*state).data[1] = value << 4;
	}
	
	// if the third byte in data is empty
	else if ( (*state).bitlength < 18){
			
		// append the 4 high-order bits of value to the second byte
		(*state).data[1] = (*state).data[1] ^ ( value >> 2 );

		// set the 2 low-order bits of value to the 2 high-order bits of the third byte
		(*state).data[2] = value << 6;
	}
	
	// filling in the last 6 bits of the total 24 bytes
	else
		(*state).data[2] = (*state).data[2] ^ ( value & 0x3F );
	
	(*state).bitlength += 6;
	(*state).length++;
}

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

int getChars( State24 *state, char buffer[] )
{
	int length = 0;
	byte values[4];
	
	// if the first data byte is not empty
	if ( (*state).bitlength >= 8 ) {
	
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
	if ( (*state).bitlength >= 16 ) {

		// 00111100 where 1111 represent the 4 low-order bits from second data byte
		byte lastFour2 = ((*state).data[1] & 0x0F) << 2;
		// get the 2 high-order bits of the third data byte
		byte firstTwo3 = ((*state).data[2] >> 6);
	
		// 'concatenate' the two to get the third character value
		values[2] = lastFour2 ^ firstTwo3;
		length++;
	}
	
	// if the third data byte is filled
	if ( (*state).bitlength == 24 ) {
	
		// get the 6 low-order bits from the third data byte
		values[3] = (*state).data[2] & 0x3F;
		length++;
	}
	
	// encode all the values as characters in the buffer array
	for ( int i = 0; i < length; i++ ) {
			
		// the value should be encoded to uppercase letter
		if ( values[i] < 0x1A )
			buffer[i] = 'A' + values[i];
		// the value should be encoded to a lowercase letter
		else if ( values[i] < 0x34 )
			buffer[i] = 'a' + values[i] - 0x1A;
		// the value should be encoded to a number
		else if ( values[i] < 0x3E )
			buffer[i] = '0' + values[i] - 0x34;
		// the value should be encoded to +
		else if ( values[i] == 0x3E )
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
