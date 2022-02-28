/**
	@file wordle.c
	@author Alex Zettlemoyer
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

bool checkGuess( const char target[], const char guess[] ) {
	bool inWord = 0;
	int correct = 0;
	
	for (int i = 0; i < WORD_LEN; i++) {
		
		// if the character is in the right spot
		if ( target[i] == guess[i] ) {
			colorGreen();
			printf("%c", guess[i]);
			correct++;
		}
		else {
			// check if the character is in the target word
			for ( int j = 0; j < WORD_LEN && !inWord; j++ ) {
				if ( guess[i] == target[j] ) {
					colorYellow();
					printf("%c", guess[i]);
					inWord = 1;
				}
			}
			// if the character wasn't in the target word
			if (!inWord) {
				colorDefault();
				printf("%c", guess[i]);
			}
		}
		
		inWord = 0;
	}
	
	colorDefault();
	printf("\n");
	return correct == 5;
}

int main( int args, char *argv[] )
{
	long seed = 0;
	bool correct = 0;
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
	
		// check if the user input is exactly 5 characters
		if ( strlen(guess) != WORD_LEN ) {
			fprintf( stderr, "Invalid guess\n" );
		}

		// check for non- lowercase characters
		for (int j = 0; j < WORD_LEN; j++) {
  			if ( guess[j] < 'a' || 'z' < guess[j] ){
				fprintf( stderr, "Invalid guess\n" );
			}
  		}
	
		guessCount++;
		correct = checkGuess(target, guess);
	}
	
	if ( guessCount == 1 )
		printf("Solved in %d guess\n", guessCount);
	else
		printf("Solved in %d guesses\n", guessCount);
	
	updateScore(guessCount);
	return 0;
}