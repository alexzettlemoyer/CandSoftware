/**
	@file database.c
	@author Alex Zettlemoyer
*/
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
 
#define INITIAL_CAPACITY 5
#define STRING_LENGTH 15

/**
	Employee Struct
	5 fields:
	id - p
*/
struct Employee {
// 	char id[STRING_LENGTH];
// 	char first[STRING_LENGTH];
// 	char last[STRING_LENGTH];
// 	char skill[STRING_LENGTH];
// 	char assignment[STRING_LENGTH];
	
	char *id;
	char *first;
	char *last;
	char *skill;
	char *assignment;
};

struct Database {
	struct Employee **employees;
	int employeeNum;
	int capacity;
};

struct Database *makeDataBase()
{
	struct Database *database = (struct Database *) malloc( sizeof( struct Database) );
	
	(*database).employees = (struct Employee **) malloc( INITIAL_CAPACITY * sizeof(struct Employee *));
	(*database).employeeNum = 0;
	(*database).capacity = INITIAL_CAPACITY;

	
	for ( int i = 0; i < INITIAL_CAPACITY; i++ ) {
		database -> employees[i] = (struct Employee *) malloc( sizeof(struct Employee));
	// 	database -> employees[i] -> id = (char *)malloc( STRING_LENGTH * sizeof( char ));
// 		database -> employees[i] -> first = (char *)malloc( STRING_LENGTH * sizeof( char ));
// 		database -> employees[i] -> last = (char *)malloc( STRING_LENGTH * sizeof(char));
// 		database -> employees[i] -> skill = (char *)malloc( STRING_LENGTH * sizeof(char));
// 		database -> employees[i] -> assignment = (char *)malloc( STRING_LENGTH * sizeof(char));
	}

	return database;
}

void freeDataBase( struct Database *database )
{
	for ( int i = 0; i < (*database).capacity; i++ ) {
		free( (*database).employees[i] -> id );
 		free( (*database).employees[i] -> first );
		free( (*database).employees[i] -> last );
		free( (*database).employees[i] -> skill );

		free( database -> employees[i] );
	}
	free( database -> employees );
	free( database );
}

void resize( struct Database *database )
{
	// double the array capacity
	(*database).capacity *= 2;
	
	// reallocate the employee list
	(*database).employees = ( struct Employee **) 
		realloc( (*database).employees, (*database).capacity * sizeof (struct Employee *));
		
	for ( int i = 0; i < (*database).capacity; i++ ) {
		database -> employees[i] = 
			(struct Employee *) realloc( database -> employees[i], sizeof(struct Employee));
	}
	
}

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
		
		
		if ( sscanf( line, "%s %s %s %s", id, first, last, skill) != 4 )
			break;		
			
		// if we are at the array capacity
		if ( count + 1 == (*database).capacity )
			resize(database);
		
		// add the employee to the next spot in the database employee list
		(*database).employees[ count ] -> id = id;
		(*database).employees[ count ] -> first = first;
		(*database).employees[ count ] -> last = last;
		(*database).employees[ count ] -> skill = skill;
		(*database).employees[ count ] -> assignment = "Available";
		
		// increase employeeCount
		count++;
		
		free(line);
	}
	
	database -> employeeNum = count;
	fclose(fp);
}

void listEmployees(struct Database *database, int (*compare)( void const *va, void const *vb ),
    bool (*test)( struct Employee const *emp, char const *str ), char const *str)
{
}

int main() {

	struct Database *d = makeDataBase();
	readEmployees("list-c.txt", d);
	
	for (int count = 0; count < 15; count++) {
	
		printf("%d:  %s ", count, (*d).employees[ count ] -> id);
		printf("%s ", (*d).employees[count] -> first);
		printf("%s ", (*d).employees[count] -> last);
		printf("%s ", (*d).employees[count] -> skill);
		printf("%s\n", (*d).employees[count] -> assignment);

	}
		
	freeDataBase(d);
	
	return  0;
}