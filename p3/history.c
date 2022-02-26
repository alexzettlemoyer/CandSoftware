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
		printf("%d : %2d\n", i, scores[i]);
	}
}

void updateScore(int guessCount)
{
	FILE *fp;
	int scores[SCORE_NUM];
	
	fp = fopen( "scores.txt", "r" );
	
	// the scores.txt file doesn't exist
	if ( fp == NULL ) {
		memset( scores, 0, sizeof(scores) );
  	}
  	else {
  		readScores(fp, scores);
  	}
  	  	
  	scores[guessCount - 1] += 1;
  	
  	printScores(fp, scores);
  	
  	fclose(fp);
}