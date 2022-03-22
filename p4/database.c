/**
	@file database.c
	@author Alex Zettlemoyer
*/
#include "database.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
 
#define INITIAL_CAPACITY 5
#define STRING_LENGTH 17
#define EXPECTED_LENGTH 15
#define ID_LENGTH 4

/**
	makeDatabase
	Database constructor
*/
struct Database *makeDataBase()
{
	// allocate space for the database struct
	struct Database *database = (struct Database *) malloc( sizeof( struct Database) );
	
	// allocate space for the list of employees
	(*database).employees = (struct Employee **) malloc( INITIAL_CAPACITY * sizeof(struct Employee *));

	// initialize employeeNum and capacity fields
	(*database).employeeNum = 0;
	(*database).capacity = INITIAL_CAPACITY;

	return database;
}

/**
	freeDataBase
*/
void freeDatabase( struct Database *database )
{
	for ( int i = 0; i < (*database).employeeNum; i++ ) {
		free( (*database).employees[i] -> id );
 		free( (*database).employees[i] -> first );
		free( (*database).employees[i] -> last );
		free( (*database).employees[i] -> skill );
		free( (*database).employees[i] -> assignment );

		free( database -> employees[i] );
	}
	free( database -> employees );
	free( database );
}

/**
	resize
*/
void resize( struct Database *database )
{
	// double the array capacity
	(*database).capacity *= 2;
	
	// reallocate the employee list
	(*database).employees = 
		realloc( (*database).employees, (*database).capacity * sizeof (struct Employee *));
		
	// reallocate each employee in the employee list
	for ( int i = 0; i < (*database).employeeNum; i++ ) {
		database -> employees[i] = 
			(struct Employee *) realloc( database -> employees[i], sizeof(struct Employee));
	}
	
}


bool checkInvalid( char const *id, char const *first, char const *last, 
	char const *skill, char const *filename, struct Database *database)
{

	
	// if the ID is not exactly 4 characters long
	if ( strlen(id) != ID_LENGTH ) {
		fprintf(stderr, "Invalid employee file: %s\n", filename);
		return false;
	}
		
	
	// if the ID is not 4 digits
	for ( int i = 0; i < ID_LENGTH; i++ ) {
		if ( id[ i ] < '0' || id[ i ] > '9') {
			fprintf(stderr, "Invalid employee file: %s\n", filename);
			return false;
		}
	}
	
	// if the ID is the same as any other in the list
	for ( int i = 0; i < (*database).employeeNum; i++ ) {
	//	printf("%s\n", (*database).employees[i] -> id);

		if ( strcmp( (*database).employees[i] -> id, id ) == 0 ) {
			fprintf(stderr, "Invalid employee file: %s\n", filename);
			return false;
		}
	}
	
	// if any of the other fields exceed 15 characters
	if ( strlen(first) > EXPECTED_LENGTH )  {
		fprintf(stderr, "Invalid employee file: %s\n", filename);
		return false;
	}
		
	if ( strlen(last) > EXPECTED_LENGTH )  {
		fprintf(stderr, "Invalid employee file: %s\n", filename);
		return false;
	}
		
	if ( strlen(skill) > EXPECTED_LENGTH )  {
		fprintf(stderr, "Invalid employee file: %s\n", filename);
		return false;
	}
	
	return true;
}

/**
	readEmployees
*/
void readEmployees( char const *filename, struct Database *database )
{
	
	FILE *fp;
    if ( ( fp = fopen( filename, "r" ) ) == NULL ) {
    	// invalid file
        fprintf( stderr, "Can't open file: %s\n", filename);
        exit( EXIT_FAILURE );
    }
    
	int count = (*database).employeeNum;
	char *line = "";
	
	while ( ( line = readLine(fp)) != NULL ) {
		
		char *id = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *first = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *last = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *skill = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *assignment = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		strcpy(assignment, "Available");		
		
		if ( sscanf( line, "%s %s %s %s", id, first, last, skill) != 4 ) {
			fprintf(stderr, "Invalid employee file: %s\n", filename);
			goto invalid;		
		}
		
		// check if the employee being read in is valid
		if ( !checkInvalid( id, first, last, skill, filename, database )) {
			
			invalid:
			
			free(id);
			free(first);
			free(last);
			free(skill);
			free(assignment);
			
			free(line);
			fclose(fp);
			freeDatabase( database );

			exit( EXIT_FAILURE);
		}
		
		// if we are at the array capacity
		if ( count == (*database).capacity )
			resize(database);
		
		// allocate space for the employee
		(*database).employees[ count ] = (struct Employee *) malloc( sizeof(struct Employee));

		// add the employee to the next spot in the database employee list
		(*database).employees[ count ] -> id = id;
		(*database).employees[ count ] -> first = first;
		(*database).employees[ count ] -> last = last;
		(*database).employees[ count ] -> skill = skill;
		(*database).employees[ count ] -> assignment = assignment;
		
		// increase employeeCount
		(*database).employeeNum++;
		count++;
		
		free(line);
	}
	
	fclose(fp);
}

/**
	listEmployees
*/
void listEmployees(struct Database *database, int (*compare)( void const *va, void const *vb ),
    bool (*test)( struct Employee const *emp, char const *str ), char const *str)
{
	qsort( database -> employees, database -> employeeNum, sizeof(database -> employees), compare);
	
	printf("%-4s %-15s %-15s %-15s %s\n", "ID", "First Name", "Last Name", "Skill", "Assignment");

	for (int i = 0; i < (database -> employeeNum); i++) {
	
		if ( test((*database).employees[i], str) ) {
			printf("%-4s ", (*database).employees[ i ] -> id);
			printf("%-15s ", (*database).employees[i] -> first);
			printf("%-15s ", (*database).employees[i] -> last);
			printf("%-15s ", (*database).employees[i] -> skill);
			printf("%-20s\n", (*database).employees[i] -> assignment);
		}
	}
}