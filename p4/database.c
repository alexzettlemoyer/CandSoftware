/**
	@file database.c
	@author Alex Zettlemoyer
*/
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 5
#define STRING_LENGTH 10

struct Employee {
	char *id;
	char *first;
	char *last;
	char skill[ STRING_LENGTH ];
	char assignment[ STRING_LENGTH ];
};

struct Database {
	struct Employee *employees;
	int employeeNum;
};

struct Database *makeDataBase()
{
	struct Database *database = {
		(struct Employee *) malloc( INITIAL_CAPACITY * sizeof(struct Employee) ), 0
	};
	
	return database;
}

void freeDataBase( struct Database *database )
{
}

void readEmployees( char const *filename, struct Database *database )
{
}

void listEmployees(struct Database *database, int (*compare)( void const *va, void const *vb ),
    bool (*test)( struct Employee const *emp, char const *str ), char const *str)
{
}