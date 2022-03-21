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
#define STRING_LENGTH 16

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
void freeDataBase( struct Database *database )
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

/**
	readEmployees
*/
void readEmployees( char const *filename, struct Database *database )
{
	
	FILE *fp;
    if ( ( fp = fopen( filename, "r" ) ) == NULL ) {
    	// usage message
        fprintf( stderr, "error\n");
        exit( EXIT_FAILURE );
    }
    
	int count = 0;
	char *line = "";
	
	while ( ( line = readLine(fp)) != NULL ) {
		
		char *id = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *first = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *last = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *skill = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		char *assignment = (char *) malloc( STRING_LENGTH * sizeof( char ) );
		strcpy(assignment, "Available");		
		
		if ( sscanf( line, "%s %s %s %s", id, first, last, skill) != 4 )
			break;		
			
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

	for (int i = 0; i < (database -> employeeNum); i++) {
	
		printf("%d:  %s ", i, (*database).employees[ i ] -> id);
		printf("%s ", (*database).employees[i] -> first);
		printf("%s ", (*database).employees[i] -> last);
		printf("%s ", (*database).employees[i] -> skill);
		printf("%s\n", (*database).employees[i] -> assignment);
	}
}