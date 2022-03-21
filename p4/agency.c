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

bool test( struct Employee const *emp, char const *str )
{
}

/**
	main method
*/
int main() 
{
	struct Database *database = makeDataBase();
	readEmployees("list-c.txt", database);
	
	for (int i = 0; i < (database -> employeeNum); i++) {
	
		printf("%d:  %s ", i, (*database).employees[ i ] -> id);
		printf("%s ", (*database).employees[i] -> first);
		printf("%s ", (*database).employees[i] -> last);
		printf("%s ", (*database).employees[i] -> skill);
		printf("%s\n", (*database).employees[i] -> assignment);
	}
	
	printf("\n");
	
	char const *str = "";
	listEmployees( database, compareId, test, str);
		
	freeDataBase(database);
	
	return  0;
}