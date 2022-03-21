/**
	@file agency.c
	@author Alex Zettlemoyer
*/
#include "input.h"
#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool test( struct Employee const *emp, char const *str )
{
	return 0;
}

/**
	compare by ID
*/
int compareId( void const *va, void const *vb ) 
{	
	struct Employee **a = ((struct Employee **) va);
	struct Employee **b = ((struct Employee **) vb);
	
	int idA = atoi( (*a) -> id);
	int idB = atoi( (*b) -> id);
	
	return idA - idB;
}

bool testAll( struct Employee const *emp, char const *str )
{
	return true;
}

bool testSkill( struct Employee const *emp, char const *str )
{
	return ( strcmp( emp -> skill, str) == 0 );
}

bool testAssignment (struct Employee const *emp, char const *str )
{
	return ( strcmp( emp -> assignment, str) == 0 );
}

/**
	main method
*/
int main( int args, char *argv[] ) 
{
	// no files given on command line
	if ( args <= 1 ) {
		fprintf( stderr, "usage: agency <employee-file>*" );
		exit( EXIT_FAILURE );
	}
	
	struct Database *database = makeDataBase();
	//char const *str = "Available";

	for ( int i = 1; i < args; i++ ) {
		readEmployees( argv[i], database );
	}
	listEmployees( database, compareId, testAll, NULL);
	
	
		
	freeDataBase(database);
	
	return  0;
}