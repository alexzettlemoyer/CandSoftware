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

/** color code for black */
#define DEFAULT 0

/** color code for green */
#define GREEN 1

/** color code for yellow */
#define YELLOW 2

/** command line argument vector index for seed */
#define SEED_INDEX 2

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
    int correct = 0;
    int color = DEFAULT; // stores the current output color: 0 black, 1 green, 2 yellow
    
    int colors[] = {0, 0, 0, 0, 0};
    int compared[] = {0, 0, 0, 0, 0};
    
    // Step 1: check for matching characters
    for ( int i = 0; i < WORD_LEN; i++ ) {
        if ( guess[i] == target[i] ) {
            colors[i] = GREEN;
            compared[i] = 1;
        }
    }
    
    // Step 2: check for matching characters in wrong spot
    for ( int i = 0; i < WORD_LEN; i++ ) {
        
        // if the current guess character hasn't already been matched
        if ( colors[i] == DEFAULT ) {
        
            // compare to remaining unmatched characters in target
            for ( int j = 0; j < WORD_LEN; j++ ) {
                
                // if the current target character hasn't already been matched
                if ( compared[j] != 1 && guess[i] == target[j] ) {
                    colors[i] = YELLOW;
                    compared[j] = 1;
                    break;
                }
            }
        }
    }
    
    // print the characters using the colors array
    for ( int i = 0; i < WORD_LEN; i++ ) {
        
        switch ( colors[i] ) {
            case GREEN:
                if ( color != GREEN ) {
                    colorGreen();
                    color = GREEN;
                }
                printf("%c", guess[i]);
                break;
            case YELLOW:
                if ( color != YELLOW ) {
                    colorYellow();
                    color = YELLOW;
                }
                printf("%c", guess[i]);
                break;
            default:
                if ( color != DEFAULT ) {
                    colorDefault();
                    color = DEFAULT;
                }
                printf("%c", guess[i]);
                break;
        }
    }
    
    if ( color != 0 ) {
        colorDefault();
        color = 0;
    }
    printf("\n");
    return correct == WORD_LEN;
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
    char guess[WORD_CHARS];
    char target[WORD_CHARS];
    
    // read the words from the given filename
    readWords(argv[1]);
        
    // if a seed was passed in
    if (args == SEED_INDEX + 1) {
        // convert the command line string argument seed into a long int
        seed = strtol( argv[SEED_INDEX] , argv + SEED_INDEX + strlen(argv[SEED_INDEX]), BASE );
    }
    // if a seed wasn't passed in use current seconds since 1970
    else {
        seed = time(NULL);
    }
    
        
    chooseWord(seed, target);
    
    // while the guess is not correct   
    while ( !correct ) {
        
        // if readLine returns false (EOF)
        if ( !readLine(stdin, guess, WORD_CHARS) ) {
            quit = 1;
            break;
        }
        
        if ( strcmp( guess, "quit") == 0 ) {
            quit = 1;
            break;
        }
    
        // check if the user input is exactly 5 characters
        if ( strlen(guess) != WORD_LEN || !inList(guess) ) {
            fprintf( stdout, "Invalid guess\n" );
            invalid = 1;
        }
        
        if ( !invalid )
            // check for non- lowercase characters
            for (int j = 0; j < WORD_LEN; j++) {
                if ( guess[j] < 'a' || 'z' < guess[j] ){
                    fprintf( stdout, "Invalid guess\n" );
                    invalid = 1;
                }
            }
            
        // if the guess wasn't invalid 
        if ( !invalid ) {
            guessCount++;
            
            if ( strcmp(target, guess) == 0 ) {
                correct = true;
                break;
            }
            else
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