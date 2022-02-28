/**
	@file history.h
	@author Alex Zettlemoyer
	header file for history.c
*/
#include <stdio.h>

/** the number of possible scores */
#define SCORE_NUM 10

/**
	readScores
	reads the current score count from the file parameter
	updates the scores array with the current score count
	@param fp the file to read from
	@param scores a 0 populated array of scores to fill
*/
void readScores(FILE *fp, int scores[]);

/**
	printScores
	prints the updated scores to stdout
	writes the updated scores to the file parameter
	@param fp the file to write the scores to
	@param scores the array of scores to print
*/
void printScores(FILE *fp, int scores[]);

/**
	updateScore
	reads in the current score, if "scores.txt" exists
	updates the score and prints it
	@param guessCount the number of guesses on this attempt to add to the score history
*/
void updateScore(int guessCount);