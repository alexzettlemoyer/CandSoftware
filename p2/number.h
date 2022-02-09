/** Exit status indicating that the program was given invalid input. */
#define FAIL_INPUT 102
#define FAIL_ZERO 101
#define FAIL_RANGE 100
#define EXIT_SUCCESS 0

/** Max and Min for char values of Base 10 characters [0-9]*/
#define BASE_10_MIN 48
#define BASE_10_MAX 57

/** ASCII value of '-' character */
#define NEGATIVE_CHAR 45

/** Max and Min for char values of Base 25 characters [A-P]*/
#define BASE_25_MIN 65
#define BASE_25_MAX 80

/** Value of the base */
#define BASE_10 10
#define BASE_25 25

/** The difference from 'A' (value 65) to it's equivalent decimal value = 10 */
#define BASE_25_CHAR_DIFF 55

/** Upper bound for Base10 numbers [0-9] */
#define BASE_10_UPPER 9

/** Function to read individual char input */
int skipSpace();
/** Function to parse multiple char values to a number value */
long parseValue();
/** Function to print a value character-by character */
void printValue( long val );