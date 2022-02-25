/**
	@file lexicon.c
	@author Alex Zettlemoyer
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
char wordList[WORD_LIMIT][WORD_LEN + 2];

/** global static variable that stores the number of words (rows) in wordList */
int wordNum;

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
    	fprintf( stderr, "Can't open word list: %s", filename );
    	exit( EXIT_FAILURE );
  	}
  	
  	wordNum = 0;
  	while ( wordNum < WORD_LIMIT && readLine(fp, wordList[wordNum], WORD_LEN) ) {  
  		
  		// if the line wasn't exactly 5 characters long
  		if ( strlen(wordList[wordNum]) != WORD_LEN ) {
  			fprintf( stderr, "Invalid word file\n" );
  			exit( EXIT_FAILURE );
  		}	
  		wordNum++;
  	}
  	
  	// the word list didn't have any words
  	if ( wordNum == 0 ) {
  		fprintf( stderr, "Invalid word file" );
  		exit( EXIT_FAILURE );
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
	inList function
	checks if the given word is already in the list
	@param word[] a constant char array to check for in the existing list
	@return true if the function is in the list, false otherwise
*/
bool inList( char const word[] )
{
	for (int i = 0; i < wordNum; i++) {
		if ( strcmp(word, wordList[i]) == 0 ) {
			return true;
		}
	}
	return false;
}