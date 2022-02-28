/**
	@file wordle.c
	@author Alex Zettlemoyer
	WORDLE program
	Program starts by reading in a list of 5 letter words
	pseudo-randomly selects a word that user must guess
	as user guesses, their guess is printed back out with green, yellow, or black chars
	indicating whether their guess has a correct letter in the right position (green)
	a correct letter in the wrong position (yellow)
	a letter that is not in the target word (black)
	Once the user has successfully guessed the word, their score history is printed
	displaying how many guesses it has taken them to correctly guess the word
*/
#include "io.h"
#include "lexicon.h"
#include "history.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/** the Base of the seed */
#define BASE 10

/**
	checkGuess function
	compares two 5 letter words
	'guess' characters in the same spot as 'target' characters are printed green
	'guess' characters that are in the 'target' string but not the same spot, yellow
	any characters in guess that are not in target are printed black (default)
	@param target the target char array
	@param guess the guessed char array
*/
bool checkGuess( const char target[], const char guess[] ) {
	bool inWord = 0;
	int correct = 0;
	
	for (int i = 0; i < WORD_LEN; i++) {
		
		// if the character is in the right spot
		if ( target[i] == guess[i] ) {
			colorGreen();
			fprintf(stdout, "%c", guess[i]);
			correct++;
		}
		else {
			// check if the character is in the target word
			for ( int j = 0; j < WORD_LEN && !inWord; j++ ) {
				if ( guess[i] == target[j] ) {
					colorYellow();
					fprintf(stdout, "%c", guess[i]);
					inWord = 1;
				}
			}
			// if the character wasn't in the target word
			if ( !inWord ) {
				colorDefault();
				fprintf(stdout, "%c", guess[i]);
			}
		}
		
		inWord = 0;
	}
	
	colorDefault();
	printf("\n");
	return correct == 5;
}

/**
	main method: starting point of the program
	provides functionality for the Wordle program
	@param args the int number of arguments passed in
	@param argv the char array argument vector
	@return exit status
*/
int main( int args, char *argv[] )
{
	long seed = 0;
	bool correct = 0;
	bool invalid = 0;
	bool quit = 0;
	int guessCount = 0;
	char guess[WORD_LEN + 1];
	char target[WORD_LEN + 1];
	
	// read the words from the given filename
	readWords(argv[1]);
	
	//printf("%zu", sizeof ( wordList ));
	
	// if a seed was passed in
	if (args == 3) {
		// convert the command line string argument seed into a long int
		seed = strtol( argv[2] , argv + 2 + strlen(argv[2]), BASE );
	}
	// if a seed wasn't passed in use current seconds since 1970
	else {
		seed = time(NULL);
	}
	
		
	chooseWord(seed, target);
	
	// while the guess is not correct	
	while ( !correct ) {
		
		readLine(stdin, guess, WORD_LEN + 1);
		
		if ( strcmp( guess, "quit") == 0 ) {
			quit = 1;
			break;
		}
	
		// check if the user input is exactly 5 characters
		if ( strlen(guess) != WORD_LEN ) {
			fprintf( stderr, "Invalid guess\n" );
			invalid = 1;
		}
		
		if ( !invalid )
			// check for non- lowercase characters
			for (int j = 0; j < WORD_LEN; j++) {
  				if ( guess[j] < 'a' || 'z' < guess[j] ){
					fprintf( stderr, "Invalid guess\n" );
					invalid = 1;
				}
  			}
  			
		// if the guess wasn't invalid 
		if ( !invalid ) {
			guessCount++;
			correct = checkGuess(target, guess);
		}
		invalid = 0;
	}
	
	if ( quit ) {
		printf( "The word was \"%s\"\n", target );
		return 0;
	}
	
	if ( guessCount == 1 )
		printf("Solved in %d guess\n", guessCount);
	else
		printf("Solved in %d guesses\n", guessCount);
	
	updateScore(guessCount);
	return 0;
}