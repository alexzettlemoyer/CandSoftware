/**
    @file calc.c
    @author Alex Zettlemoyer
    Program that reads in a line of numbers and operators
    (in either base 10 or base 25)
    performs the operations on input numbers
    and outputs the result in the given base
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
    int nextChar;
    long value = parseTerm();
        
    while (operator != EOF && operator != '\n') {

        operator = skipSpace();
        
        if (operator == EOF || operator == '\n') {
            break;
        }
        
        // look at the next character
        nextChar = skipSpace();
        // check that the next character isn't an operator
        if ( nextChar == '+'|| nextChar == '*' || nextChar == '/')
            exit(FAIL_INPUT);
        // put it back into the inputStream if it wasn't
        ungetc(nextChar, stdin);

        val2 = parseTerm();
        
        if (operator == '+') {
        //  printf("%ldplus%ld=", value, val2);
            value = plus(value, val2);
        //  printf("%ld\n", value);
        }
        else if (operator == '-') {
        //  printf("%ldminus%ld=", value, val2);
            value = minus(value, val2);
        //  printf("%ld\n", value);
        }
    }
    printValue(value);
    printf("\n");
    return EXIT_SUCCESS;
}