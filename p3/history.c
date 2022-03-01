/**
    @file history.c
    @author Alex Zettlemoyer
    History handles the score history
    reads and writes to "scores.txt" to maintain score history
    prints out the updated score count
*/

#include "history.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** the number of possible scores */
#define SCORE_NUM 10

/**
    readScores
    reads the current score count from the file parameter
    updates the scores array with the current score count
    @param fp the file to read from
    @param scores a 0 populated array of scores to fill
*/
void readScores(FILE *fp, int scores[])
{
    for (int i = 0; i < SCORE_NUM; i++) {
        fscanf(fp, "%d ", &scores[i]);
    }
}

/**
    printScores
    prints the updated scores to stdout
    writes the updated scores to the file parameter
    @param fp the file to write the scores to
    @param scores the array of scores to print
*/
void printScores(FILE *fp, int scores[])
{
    for(int i = 0; i < SCORE_NUM; i++) {
        
        if ( i + 1 < SCORE_NUM ) {
            fprintf(fp, "%d ", scores[i]);
            printf("%2d  :  %3d\n", i + 1, scores[i]);
        }
        else {
            fprintf(fp, "%d", scores[i]);
            printf("%2d+ :  %3d\n", i+ 1, scores[i]);
        }
    }
    fprintf(fp, "\n");
}

/**
    updateScore
    reads in the current score, if "scores.txt" exists
    updates the score and prints it
    @param guessCount the number of guesses on this attempt to add to the score history
*/
void updateScore(int guessCount)
{
    FILE *fp;
    
    // make a new scores array
    int scores[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        
    // the scores.txt file exists
    if ( ( fp = fopen( "scores.txt", "rb+" ) ) != NULL )
        readScores(fp, scores);
        
    if ( guessCount >= SCORE_NUM )  
        scores[ SCORE_NUM -1 ] += 1;
    else
        scores[guessCount - 1] += 1;
    
    // open in write mode
    fp = fopen( "scores.txt", "w" );
    printScores(fp, scores);
    
    fclose(fp);
}