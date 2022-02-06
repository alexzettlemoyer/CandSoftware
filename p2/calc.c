/**
	@file calc.c
	@author Alex Zettlemoyer
*/
#include number.h
#include operation.h
#include <stdio.h>

static long parseTerm()
{
	long value;
	int input = 0;
	long val1 = 0;
	long val2 = 1;
	
	val1 = parseValue();
	char ch = skipSpace();
	val2 = parseValue();
	value = val1;
	
	if (ch == '*')
		value = times(val1, val2);
	if (ch == '/')
		value = divide(val1, val2);
	if (ch == '+' || ch == '-' || ch == '\n' || ch == EOF)
		unget(ch, stdin);
	
	return value;
}

int main() 
{
	
	
	return 0;
}