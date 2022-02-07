/**
	@file calc.c
	@author Alex Zettlemoyer
*/
#include "number.h"
#include "operation.h"
#include <stdio.h>
#include <stdlib.h>

static long parseTerm()
{
	long value;
	long val1 = 0;
	long val2 = 1;
	
	val1 = parseValue();
	char ch = skipSpace();
	
	if (ch == '+' || ch == '-' || ch == '\n' || ch == EOF)
		ungetc(ch, stdin);
		return val1;
		
	val2 = parseValue();
	
	if (ch == '*')
		value = times(val1, val2);
	if (ch == '/')
		value = divide(val1, val2);
	
	return value;
}

int main() 
{
	long value;
	long val1;
	long val2;
	char operator = ' ';
	
	while (operator != EOF && operator != '\n') {
		val1 = parseTerm();
		operator = skipSpace();
		
		if (operator == EOF || operator == '\n')
			break;
		
		val2 = parseTerm();
		
		if (operator == '+') 
			value += plus(val1, val2);
		if (operator == '-')
			value += minus(val1, val2);
	}
	printValue(value);
	return 0;
}