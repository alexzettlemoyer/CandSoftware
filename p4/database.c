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
	struct Database database = {
		.employees = malloc( INITIAL_CAPACITY * sizeof(struct Employee) ), 
		.employeeNum = 0,
		.capacity = INITIAL_CAPACITY
	};
	
	// for ( int i = 0; i < INITIAL_CAPACITY; i++ )
// 		database.employees[i] = malloc( sizeof(struct Employee));
	
	struct Database *ptrDB = &database;
	return ptrDB;
}

void freeDataBase( struct Database *database )
{
	for ( int i = 0; i < (*database).employeeNum; i++ ) {
		free( (*database).employees[i]);
	}
	free( (*database).employees);
	free( database );
}

void resize( struct Database *database )
{
	// double the array capacity
	(*database).capacity *= 2;
	
	// reallocate the employee list
	*(*database).employees = ( struct Employee *) 
		realloc ((*database).employees, (*database).capacity * sizeof (struct Employee ));
}

void readEmployees( char const *filename, struct Database *database )
{
	FILE *fp = fopen(filename, "r");
	int i = 0;
	printf("EmployeeNum %d\n", database -> employeeNum );
		printf("capacity %d\n", database -> capacity );


	char *line = readLine(fp);
	
	while ( line != NULL ) {
		char id[STRING_LENGTH];
		char first[STRING_LENGTH];
		char last[STRING_LENGTH];
		char skill[STRING_LENGTH];
		
		if ( sscanf( line, "%s %s %s %s", id, first, last, skill) != 4 )
			break;
		
		printf("%s %s %s %s\n", id, first, last, skill);
		
		if ( (*database).employeeNum + 1 == (*database).capacity )
			resize(database);
		
		struct Employee *e =  malloc( sizeof(struct Employee));
		struct Employee eInstance = {id, first, last, skill, "Available"};
		e = &eInstance;
		
// 		printf("%s\n", (*database).employees);
		
// 		(*database).employees[0] -> id = "1234";
		// (*database).employees[ (*database).employeeNum] -> first = first;
// 		(*database).employees[ (*database).employeeNum] -> last = last;
// 		(*database).employees[ (*database).employeeNum] -> skill = skill;
// 		(*database).employees[ (*database).employeeNum ++ ] -> assignment = "Available";


		// add the employee to the next spot in the database employee list and increase
		(*database).employees[ i ] = e;
		i++;
		
		line = readLine(fp);
	}
	
	printf("%d", database -> employeeNum);
	(*database).employeeNum = i;
	
	fclose(fp);
}

void listEmployees(struct Database *database, int (*compare)( void const *va, void const *vb ),
    bool (*test)( struct Employee const *emp, char const *str ), char const *str)
{
}

int main() {

	struct Database *d = makeDataBase();
	printf("EmployeeNum %d\n", d -> employeeNum );

	readEmployees("list-b.txt", d);
	freeDataBase(d);
	
	return  0;
}