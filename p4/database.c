/**
    @file database.c
    @author Alex Zettlemoyer
    handles functions that relate to manipulating the database
    makeDatabse instantiates a Database struct
    freeDatabase frees the memory of a Database struct
    resize is responsible for resizing the Databases employee list
    checkValid checks whether an employee is valid
    readEmployees reads in a list of employees and stores them in the database
    listEmployees prints a list of the employees
*/
#include "database.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
 
 /** Initial Array capacity for the resizable array of pointers-to-Employees */
#define INITIAL_CAPACITY 5
/** Length of String to read in 15 + 1 to check for length + 1 for null termination */
#define STRING_LENGTH 17
/** Expected length of first, last, skill employee field Strings */
#define EXPECTED_LENGTH 15
/** Expected length of the employee ID field String */
#define ID_LENGTH 4
/** Expected number of Employee fields on one line in employee txt file */
#define EXPCT_FIELDS 4

/**
    makeDatabase
    Database constructor
    Allocates space for a Database struct
    Allocates space for an array of Employee pointers
    Initializes the number of employees to 0
    Initializes the capacity of the resizable employee array to 5
    @return a pointer to the database malloc'd
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
    frees the memory allocated for all of the employee fields and employees
    frees the memory allocated for the array of pointer-to-Employees
    frees the memory allocated for the database
    @param database a pointer to the database to free
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
    Resizes the employee list of the database
    doubles the capacity of the pointer-to-Employee list
    reallocates space for the new capacity of the list
    reallocates the existing employees into the new list
    @param database a pointer to the database to resize
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
    checkValid
    checks whether an employee is valid or not
    Valid employees have an ID of 4 digits that is different from other ID's in the list
    and first, last, and skill Strings of length less than 15
    @param id the Employee ID to check
    @param first the Employee first name to check
    @param last the Employee last name to check
    @param skill the Employee skill to check
    @param filename the filename to print in error message (if invalid)
    @param database the database to check for unique IDs
    @return true if valid, false otherwise
*/
bool checkValid( char const *id, char const *first, char const *last, 
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
    Reads in a list of Employees from the given file, allocates space for them,
    and adds them to the database's pointer-to-Employee list
    Resizes the pointer-to-Employee list if the capacity is exceeded
    Exits the program if the file cannot be opened
    Exits the program if any of the employees are invalid
    @param filename the name of the file to read Employees from
    @param database pointer to the database to add Employees to
*/
void readEmployees( char const *filename, struct Database *database )
{
    
    FILE *fp;
    // attempt to open the file
    if ( ( fp = fopen( filename, "r" ) ) == NULL ) {
        // invalid file
        fprintf( stderr, "Can't open file: %s\n", filename);
        freeDatabase( database );
        exit( EXIT_FAILURE );
    }
    
    // start with the count at employeeNum
    int count = (*database).employeeNum;
    char *line = "";
    
    // read an employee line
    while ( ( line = readLine(fp)) != NULL ) {
        
        char *id = (char *) malloc( STRING_LENGTH * sizeof( char ) );
        char *first = (char *) malloc( STRING_LENGTH * sizeof( char ) );
        char *last = (char *) malloc( STRING_LENGTH * sizeof( char ) );
        char *skill = (char *) malloc( STRING_LENGTH * sizeof( char ) );
        char *assignment = (char *) malloc( STRING_LENGTH * sizeof( char ) );
        strcpy(assignment, "Available");        
        
        // check that each employee has only 4 fields
        if ( sscanf( line, "%s %s %s %s %s", id, first, last, skill, assignment) != EXPCT_FIELDS ) {
            fprintf(stderr, "Invalid employee file: %s\n", filename);
            goto invalid;       
        }
        
        // check if the employee being read in is valid
        if ( !checkValid( id, first, last, skill, filename, database )) {
            
            // if the employee is invalid
            invalid:
            
            // free all the fields before quitting the program
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
    Quicksorts the list of employees using the given compare function
    Prints the list of employees given the test and str parameters
    @param database the database to sort
    @param compare the compare function to use when sorting
    @param test the test to check which employees to list
    @param str the String to check which employees to list
*/
void listEmployees(struct Database *database, int (*compare)( void const *va, void const *vb ),
    bool (*test)( struct Employee const *emp, char const *str ), char const *str)
{

    // quicksort the employees using given comparator
    qsort( database -> employees, database -> employeeNum, sizeof(database -> employees), compare);
    
    // format the header line
    printf("%-4s %-15s %-15s %-15s %s\n", "ID", "First Name", "Last Name", "Skill", "Assignment");

    // print each employee in the list
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