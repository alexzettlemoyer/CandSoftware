/**
	@file database.h
	@author Alex Zettlemoyer
	header file for database.c
	database handling for agency.c
*/
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
	Employee Struct
	id String ( 4 digits )
	first name String ( maximum 15 characters )
	last name String ( maximum 15 characters )
	skill String ( maximum 15 characters )
	assignment String ( maximum 20 characters )
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
	list of pointer-to-Employee struct
	employeeNum integer stores the number of employees in the list
	capacity integer stores the current capacity of the list
*/
struct Database {
	struct Employee **employees;
	int employeeNum;
	int capacity;
};

/**
	makeDatabase
	Database constructor
	Allocates space for a Database struct
	Allocates space for an array of Employee pointers
	Initializes the number of employees to 0
	Initializes the capacity of the resizable employee array to 5
	@return a pointer to the database malloc'd
*/
struct Database *makeDataBase();

/**
	readEmployees
	Reads in a list of Employees from the given file, allocates space for them,
	and adds them to the database's pointer-to-Employee list
	Resizes the pointer-to-Employee list if the capacity is exceeded
	Exits the program if the file cannot be opened
	Exits the program if any of the employees are invalid
	@param filename the name of the file to read Employees from
	@param database pointer to the database to add Employees to
*/
void readEmployees( char const *filename, struct Database *database );

/**
	listEmployees
	Quicksorts the list of employees using the given compare function
	Prints the list of employees given the test and str parameters
	@param database the database to sort
	@param compare the compare function to use when sorting
	@param test the test to check which employees to list
	@param str the String to check which employees to list
*/
void listEmployees(struct Database *database, int (*compare)( void const *va, void const *vb ),
    bool (*test)( struct Employee const *emp, char const *str ), char const *str);

/**
	freeDataBase
	frees the memory allocated for all of the employee fields and employees
	frees the memory allocated for the array of pointer-to-Employees
	frees the memory allocated for the database
	@param database a pointer to the database to free
*/
void freeDatabase(struct Database *database);