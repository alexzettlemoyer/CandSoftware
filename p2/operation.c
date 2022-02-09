/**
    @file operation.c
    @author Alex Zettlemoyer
    contains functions for four arithmetic operations
    plus, minus, times, and divide
    checks for overflow in Long int after each operation
*/
#include "number.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
    plus
    adds the two long parameters together
    checks if the addition caused overflow
    exits with status 102 if overflow occurred
    @param a the first value
    @param b the second value
    @return the result of the addition
*/
long plus( long a, long b )
{
    long result = a + b;
    
    // two positives = negative -> overflow
    if (a > 0 && b > 0 && result < 0) {
        exit(FAIL_RANGE);
    }
    // two negatives = positive -> overflow
    if (a < 0 && b < 0 && result > 0) {
        exit(FAIL_RANGE);
    }
    
    return result;
}

/**
    minus
    subtracts second long parameter from first
    checks if subtraction caused overflow
    exits with status 102 if overflow occurred
    @param a the value to be subtracted from
    @param b the value to subtract
    @return the result of the subtraction
*/
long minus( long a, long b )
{
    long result = a - b;
    
    // negative - positive = positive
    if ( a < 0 && b > 0 && result > 0) {
        exit(FAIL_RANGE);
    }
    
    // positive - negative = negative
    if ( a > 0 && b < 0 && result < 0) {
        exit(FAIL_RANGE);
    }
    
    return result;
}

/**
    times
    multiplies the two long parameters together
    checks if multiplication caused overflow
    exits with status 102 if overflow occurred
    @param a the first value
    @param b the second value
    @return the result of the multiplication
*/
long times( long a, long b )
{
    long result = a * b;
    
    // two positives = negative
    if (a > 0 && b > 0 && result < 0) {
        exit(FAIL_RANGE);
    }
    // two negatives = negative
    if (a < 0 && b < 0 && result > 0) {
        exit(FAIL_RANGE);
    }
    // 1 negative * 1 positive = positive
    if ((a < 0 && b > 0 && result > 0) || (a > 0 && b < 0 && result > 0)) {
        exit(FAIL_RANGE);
    }
    
    if (result < LONG_MIN || result > LONG_MAX) {
        exit(FAIL_RANGE);
    }
    
    return result;
}

/**
    divide
    divides first long parameter by the second
    checks if the divisor is 0
    exits with status 101 if dividing by 0
    @param a the dividend
    @param b the divisor
    @return the result of the division
*/
long divide( long a, long b )
{
    // trying to divide by 0
    if (b == 0) {
        exit(FAIL_ZERO);
    }
    
    long result = a / b;
    
    return result;
}