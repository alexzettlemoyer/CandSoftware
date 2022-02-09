/**
    @file number25.c
    @author Alex Zettlemoyer
*/
#include "number.h"
#include "operation.h"
#include <stdio.h>
#include <stdlib.h>


/**
    skipSpace
    scans until reaching a non-WhiteSpace character
    non-WhiteSpace includes EOF and \n
    @return the int code for the first non-WhiteSpace character
*/
int skipSpace()
{
    char ch;
    
    while (scanf("%c", &ch) == 1) {
    
        if (ch != ' ' && ch != '\f' && ch != '\t' && ch != '\r' && ch != '\v'){
            if (ch == EOF) {
                return EOF;
            }
            if (ch == '\n') {
                return '\n';
            }
            if (!((BASE_10_MIN <= ch && ch <= BASE_10_MAX) ||
                    (BASE_25_MIN <= ch && ch <= BASE_25_MAX) 
                    || ch == '-' || ch == '+' || ch == '/' || ch == '*')) {
                exit(FAIL_INPUT);
            }
                    
            return ch;
        }
    }
    return EOF; 
}

/**
    reads in the next value from input in Base 25
    parses the char to a long integer value
    @return the long int value parsed
*/
long parseValue()
{
    int charVal = skipSpace();
    int numVal;
    long value = 0;
    _Bool negative = 0;
    
    // checks if there's a negative before the number
    if (charVal == NEGATIVE_CHAR) {
        negative = 1;
        charVal = skipSpace();
    }   
    
    // while the character is a Base 25 number [0-9] or [A-P]
    while ( (BASE_10_MIN <= charVal && charVal <= BASE_10_MAX) ||
                (BASE_25_MIN <= charVal && charVal <= BASE_25_MAX) ) {
            
            // if it's a digit  
        if (BASE_10_MIN <= charVal && charVal <= BASE_10_MAX)
            numVal = charVal - 48;
        else
            numVal = charVal - 55;
        
        // slide all values over one
        value = times(value, 25);
                
        // add in the new value
        value = plus(value, numVal);
        
        charVal = skipSpace();
    }
    
    // change the number to a negative if it had a '-' char in front
    if (negative == 1) {
        value *= -1;
    }
    
    char character = charVal;
    
    // add back the operator read in
    ungetc(character, stdin);
    
    return value;
}


/**
    prints the value as a long integer in Base25
    @param val the value to print
*/
void printValue( long val )
{
    int digit = 0;
    char ch;
    
    if (val < 0) {
        // print the negative sign
        printf("%c", '-');
        
        // get the next digit on the right
        digit = val % -25;
        digit *= -1;
        
        // if the digit is [0-9]
        if (0 <= digit && digit <= 9)
            ch = (char) digit + 48;
        else
            ch = (char) digit + 55;
    
        if (val / 25 != 0)
            printValue(val / -25);
        
        printf("%c", ch);
        
        // print the rest of the positive version of the value
        //printValue(val * -1);
    }   
    else if (val != 0) {
        // get the next digit on the right
        digit = val % 25;
        
        // if the digit is [0-9]
        if (0 <= digit && digit <= 9)
            ch = (char) digit + 48;
        else
            ch = (char) digit + 55;
    
        if (val / 25 != 0)
            printValue(val / 25);
            
        printf("%c", ch);
    }
    else {
        printf("%ld", val);
    }
}