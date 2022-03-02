/**
    @file lexicon.c
    @author Alex Zettlemoyer
    stores the list of words and provides the functions for using it
    readWords reads in a text file and checks for errors
    chooseWord randomly chooses a word from the list
    inList checks if a given word is in the word list
*/
#include "lexicon.h"
#include "io.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** Large prime multiplier used to choose a word pseudo-randomly. */
#define MULTIPLIER 4611686018453

/** global static variable to store list of words */
char wordList[WORD_LIMIT][WORD_CHARS];

/** global static variable that stores the number of words (rows) in wordList */
int wordNum;

/** report that the word file is invalid and exit unsuccessfully */
static void invalid()
{
    fprintf(stderr, "Invalid word file\n" );
    exit(EXIT_FAILURE);
}


/** 
    readWords function
    function to read in word list from file with the given name
    detects errors in the word list file and prints error message
    @param filename a constant char[] that contains the filename to read
*/
void readWords (char const filename[] )
{
    FILE *fp;
    if ( ( fp = fopen( filename, "r" ) ) == NULL ) {
        fprintf( stderr, "Can't open word list: %s\n", filename );
        exit( EXIT_FAILURE );
    }
    
    wordNum = 0;
    while ( wordNum < WORD_LIMIT && readLine(fp, wordList[wordNum], WORD_LEN + 1) ) {  
                
        // if the line wasn't exactly 5 characters long
        if ( strlen(wordList[wordNum]) != WORD_LEN )
            invalid();
        wordNum++;
    }
    
    // the word list didn't have any words
    if ( wordNum == 0 || wordNum == WORD_LIMIT )
        invalid();
    
    // error handling:
        
    char str[WORD_LEN + 1];
    // for each word in the word list
    for (int i = 0; i < wordNum; i++) {
        strcpy( str, wordList[i] );
        
        // check for non- lowercase characters
        for (int j = 0; j < WORD_LEN; j++) {
            if ( str[j] < 'a' || 'z' < str[j] )
                invalid();
        }   
    }
    fclose(fp);
}

/**
    checkDuplicates function
    checks for duplicate words in the wordList array
    because the list is sorted, 
    this function compares each element to the element before and after it
    prints invalid and exits unsuccessfully if a duplicate is found
*/
void checkDuplicates() 
{
    for ( int i = 0; i < wordNum; i++ ) {
    
        if ( i > 0 && strcmp(wordList[i - 1], wordList[i]) == 0 )
            invalid();
        if ( i < wordNum - 1 && strcmp(wordList[i], wordList[i + 1]) == 0)
            invalid();
    }
}

/**
    chooseWord function
    chooses a word from the current word list 
    copies the chosen word into the word[] array
    @param seed the seed value to use
    @param word[] the char array to copy the chosen word into
*/
void chooseWord( long seed, char word[] )
{
    int wordIndex = (seed % wordNum) * MULTIPLIER % wordNum;
    strcpy(word, wordList[wordIndex]);
}


/**
    binarySearch function
    implemented recursively
    compares the target word to the middle element
    recursively searches the lower / upper half based on comparison
    references:
    - CSC 316 Workshop 5 ( Java binary search implementation )
    @param min the minimum index to search
    @param max the maximum index to search
    @param target the string to search for
    @return the index of the target string, -1 if not in list
*/
int binarySearch( int min, int max, const char target[] ) 
{
    
    if ( min > max ) 
        return -1;
    
    int mid = ( max + min ) / 2;
    
    // target word is at middle index
    if ( strcmp( wordList[mid], target ) == 0 )
        return mid;
    // target is less than middle index
    else if ( strcmp( wordList[mid], target ) > 0 )
        // search left half
        return binarySearch( min, mid - 1, target );
    else
        // search right half
        return binarySearch( mid + 1, max, target );
}

/**
    inList function
    checks if the given word is already in the list
    implemented using binary search
    @param word[] a constant char array to check for in the existing list
    @return true if the function is in the list, false otherwise
*/
bool inList( char const word[] )
{
    return binarySearch( 0, wordNum, word ) >= 0;
}

/**
    swap helper function for quickSort
    swaps the Strings in the given pointers
    @param *a char pointer to the first string
    @param *b char pointer to the second string
*/
void swap( char *a, char *b ) 
{
    for ( int i = 0; i < WORD_LEN; i++ ) {
        char temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

/**
    quickSort function
    implemented recursively
    chooses the middle element as the pivot point
    moves elements < pivot to the left half
    moves elements > pivot to right half
    recursively sorts left and right half
    references:
    - CSC 316 Workshop 4 ( Java QuickSorter implementation )
    @param low the lowest index to sort
    @param high the highest index to sort
*/
void quickSort( int low, int high ) 
{
    int pivot = ( low + high ) / 2 ;

    if ( low < high ) {
        // swap the pivot with the last element
        swap( wordList[pivot], wordList[high] );
        
        // start the pivot point at the first element
        pivot = low;
        
        // traverse the array from the first to last element
        for ( int i = low; i < high; i++ ) {

            // if the current element is < than the pivot element 
            if ( strcmp( wordList[i], wordList[high] ) <= 0 ) {
                // swap the current element with the current pivot point
                swap( wordList[i], wordList[pivot] );
                pivot++;
            }
        }

        swap( wordList[pivot], wordList[high] );

        // sort the left half
        quickSort( low, pivot - 1 );
        // sort the right half
        quickSort( pivot + 1, high );
    }
}

/**
    sortList function
    implemented using quickSort
    calls the quickSort function to sort the list
*/
void sortList() 
{
    quickSort(0, wordNum - 1);
}