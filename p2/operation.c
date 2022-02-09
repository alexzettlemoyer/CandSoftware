/**
	@file operation.c
	@author Alex Zettlemoyer
*/
#include "number.h"
#include "operation.h"
#include <stdio.h>
#include <stdlib.h>

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
	
	// out of long range
	if (result < LONG_MIN || result > LONG_MAX) {
		exit(FAIL_RANGE);
	}
	
	return result;
}

long minus( long a, long b )
{
	long result = a - b;
		
	// out of long range
	if (result < LONG_MIN || result > LONG_MAX) {
		exit(FAIL_RANGE);
	}
	
	return result;
}

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

long divide( long a, long b )
{
	// trying to divide by 0
	if (b == 0) {
		exit(FAIL_ZERO);
	}
	
	long result = a / b;
	
	if (result < LONG_MIN || result > LONG_MAX) {
		exit(FAIL_RANGE);
	}
	
	return result;
}