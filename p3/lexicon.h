/**
    @file lexicon.h
    @author Alex Zettlemoyer
    header file for lexicon.c
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/** Maximum lengh of a word on the word list. */
#define WORD_LEN 5

/** 
    Number of chars for a char array for a word in the list.
    Allows 2 extra characters for null termination
    and to check for word length overflow
*/
#define WORD_CHARS 7

/** Maximum number of words on the word list. */
#define WORD_LIMIT 100000

/** Exit status with failed input */
#define EXIT_FAILURE 1

/**
    wordList will store the input list of words
    stores 100,000 char arrays
    each of the char arrays has length 7
    to account for 5 character words
    + 1 to check if the line had > 5 characters
    + 1 as a space for null termination
*/
extern char wordList[WORD_LIMIT][WORD_CHARS];

/** 
    readWords function
    function to read in word list from file with the given name
    detects errors in the word list file and prints error message
    @param filename a constant char[] that contains the filename to read
*/
void readWords(char const filename[]);

/**
	checkDuplicates function
	checks for duplicate words in the wordList array
	because the list is sorted, 
	this function compares each element to the element before and after it
    prints invalid and exits unsuccessfully if a duplicate is found
*/
void checkDuplicates();

/**
    chooseWord function
    chooses a word from the current word list 
    copies the chosen word into the word[] array
    @param seed the seed value to use
    @param word[] the char array to copy the chosen word into
*/
void chooseWord(long seed, char word[]);

/**
    inList function
    checks if the given word is already in the list
    implemented using binary search
    @param word[] a constant char array to check for in the existing list
    @return true if the function is in the list, false otherwise
*/
bool inList(char const word[]);

/**
	sortList function
	implemented using quickSort
	calls the quickSort function to sort the list
*/
void sortList();