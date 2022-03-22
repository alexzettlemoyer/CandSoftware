/**
	@file database.h
	@author Alex Zettlemoyer
*/
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
	Employee Struct
*/
struct Employee {
	char *id;
	char *first;
	char *last;
	char *skill;
	char *assignment;
};

/**
	Database Struct
*/
struct Database {
	struct Employee **employees;
	int employeeNum;
	int capacity;
};

struct Database *makeDataBase();

void readEmployees( char const *filename, struct Database *database );

void listEmployees(struct Database *database, int (*compare)( void const *va, void const *vb ),
    bool (*test)( struct Employee const *emp, char const *str ), char const *str);

void freeDatabase(struct Database *database);