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
int main() 
{
	struct Database *database = makeDataBase();
	readEmployees("list-c.txt", database);
		
	char const *str = "Available";
	listEmployees( database, compareId, testAssignment, str);
		
	freeDataBase(database);
	
	return  0;
}