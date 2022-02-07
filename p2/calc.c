/**
	@file calc.c
	@author Alex Zettlemoyer
*/
#include "number.h"
#include "operation.h"
#include <stdio.h>
#include <stdlib.h>

/**
	parseTerm
	calculates the result of one * or / operation
	if the 'term' only has one number, it is returned
	@return long result of the operation
*/
static long parseTerm()
{
	long value;
	long val1 = parseValue();
	long val2 = 1;
	
	char operator = ' ';
	
	while (operator != '+' && operator != '-' && operator != '\n' && operator != EOF) {
		
		operator = skipSpace();
		
		if (operator == '+' || operator == '-' || operator == '\n' || operator == EOF) {
			ungetc(operator, stdin);
			return val1;
		}
		
		val2 = parseValue();
	
		if (operator == '*')
			value = times(val1, val2);
		if (operator == '/')
			value = divide(val1, val2);
		val1 = value;
	}
	
	return value;
}

/**
	starting point of program
	loops over + and - operations and calculates them
	delegating to parseTerm
	until reaching EOF or a newLine
	@return exit status
*/
int main() 
{
	long val2 = 0;
	char operator = ' ';
	long value = parseTerm();
	
	while (operator != EOF && operator != '\n') {

		operator = skipSpace();
		
		if (operator == EOF || operator == '\n') {
			break;
		}

		val2 = parseTerm();
		
		if (operator == '+') {
			value = plus(value, val2);
		}
		else if (operator == '-') {
			value = minus(value, val2);
		}
	}
	printValue(value);
	return 0;
}