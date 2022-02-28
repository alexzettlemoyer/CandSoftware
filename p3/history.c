/**
	@file history.c
	@author Alex Zettlemoyer
*/

#include "history.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void readScores(FILE *fp, int scores[])
{
	fp = fopen("scores.txt", "w");
	for (int i = 0; i < SCORE_NUM; i++) {
		fscanf(fp, "%d ", &scores[i]);
	}
}

void printScores(FILE *fp, int scores[])
{
	for(int i = 0; i < SCORE_NUM; i++) {
		fprintf(fp, "%d ", scores[i]);
		
		if ( i + 1 < 10 )
			printf("%2d  : %2d\n", i + 1, scores[i]);
		else
			printf("%2d+ : %2d\n", i+ 1, scores[i]);
	}
}

void updateScore(int guessCount)
{
	FILE *fp;
	int scores[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		
	// the scores.txt file exists
	if ( ( fp = fopen( "scores.txt", "ab+" ) ) != NULL )
  		readScores(fp, scores);
  	  	
  	scores[guessCount - 1] += 1;
  	
  	printScores(fp, scores);
  	
  	fclose(fp);
}