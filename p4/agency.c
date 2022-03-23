/**
    @file agency.c
    @author Alex Zettlemoyer
    Agency program manages a database of employees
    Provides functions for companies to contract 
    the agency to hire employees on a temporary basis
    Program takes 1 or more file names of employees on the command line
*/
#include "input.h"
#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** Expected max length of a command */
#define CMD_LENGTH 10
/** Length of a command string 10 +1 to check length +1 for null termination */
#define CMD2_LENGTH 12
/** Expected max length of the assignment command */
#define ASSIGNMENT_LENGTH 20
/** Length of an assignment command string 20 +1 to check length +1 for null termination */
#define CMD3_LENGTH 22
/** Expected length of an ID */
#define ID_LENGTH 4
/** Expected maximum number of command line arguments */
#define MAX_COMMAND_NUM 3


/**
    compare by ID
    converts the Employee's id to an integer and compares them
    @param va constant void pointer to employee 1
    @param vb constant void pointer to employee 2
    @return the integer value of the comparison
*/
int compareId( void const *va, void const *vb ) 
{   
    // cast to Employee
    struct Employee **a = ((struct Employee **) va);
    struct Employee **b = ((struct Employee **) vb);
    
    // convert to integer
    int idA = atoi( (*a) -> id);
    int idB = atoi( (*b) -> id);
    
    // return the difference
    return idA - idB;
}

/**
    compare by Skill
    compares the skill of two employees
    if the skills are equal, delegates to compareID for comparison
    @param va constant void pointer to employee 1
    @param vb constant void pointer to employee 2
    @return the integer value of the String comparison
*/
int compareSkill( void const *va, void const *vb )
{
    struct Employee **a = ((struct Employee **) va);
    struct Employee **b = ((struct Employee **) vb);
    
    int compare = strcmp( (*a) -> skill, (*b) -> skill );
    
    if ( compare == 0 )
        compare = compareId( va, vb );
    
    return compare;
}

/**
    testAll
    always returns true
    ( used to print all employees in database.c listEmployees function )
    @param emp a constant employee struct
    @param str a String
    @param true for any employee and any string
*/
bool testAll( struct Employee const *emp, char const *str )
{
    return true;
}

/** 
    testSkill
    compares the given employee's skill with the skill in the str parameter
    @param emp a constant employee struct
    @param str a String of the skill to test for
    @param true if emp's skill and str match, false otherwise
*/
bool testSkill( struct Employee const *emp, char const *str )
{
    return ( strcmp( emp -> skill, str) == 0 );
}

/** 
    testAssignment
    compares the given employee's assignment with the assignment in the str parameter
    @param emp a constant employee struct
    @param str a String of the assignment to test for
    @param true if emp's assignment and str match, false otherwise
*/
bool testAssignment (struct Employee const *emp, char const *str )
{
    return ( strcmp( emp -> assignment, str) == 0 );
}

/**
    assign method
    works for both the assign and unassign operation
    assign: sets the given employee ID's assignment to the assignment parameter
    unassign: sets the given employee ID's assignment to "Available"
    @param assign true if assign operation, false if unassign operation
    @param id the ID to assign/unassign
    @param assignment the new assignment or "Available" if unassigning
    @param database to check for the given employee ID
    @return true if the assignment was possible, false otherwise
*/
bool assign( bool assign, char *id, char *assignment, struct Database *database )
{
    bool found = 0;

    if ( strlen(assignment) > ASSIGNMENT_LENGTH || strlen(id) != ID_LENGTH )
        return found;
    else {
        // traverse all the employees
        for ( int i = 0; i < (*database).employeeNum; i++ ) {
            
            // if we found the employee with the same id
            if ( strcmp((*database).employees[i] -> id, id) == 0 ) {
            
                // if assign & "Available" or unassign and !"Available"
                if ( assign ==
                (strcmp((*database).employees[i] -> assignment, "Available") == 0) ) {
                    
                    // update the employee's assignment!
                    strcpy((*database).employees[i] -> assignment, assignment);
                    found = true;
                }           
            }
        }
    }
    // the employee wasn't found in the given list
    // or the current assignment didn't allow for assigning/unassigning
    return found;
}

/**
    main method
    reads in each list of employees from the argument vector
    puts all the employees into a database
    allows user commands "list", "assign", "unassign", "quit"
    continues to prompt the user until 'quit' is input
    @param args the number of command line arguments
    @param argv Argument Vector containing 1 or more employee lists to read
    @return exit status
*/
int main( int args, char *argv[] ) 
{
    // no files given on command line
    if ( args <= 1 ) {
        fprintf( stderr, "usage: agency <employee-file>*\n" );
        exit( EXIT_FAILURE );
    }
    
    // make the database
    struct Database *database = makeDataBase();

    // read in each list in the argument vector
    for ( int i = 1; i < args; i++ ) {
        readEmployees( argv[i], database );
    }
    
    int commands = 0;
    
    char *input;
    char *cmd1 = (char *) malloc( CMD_LENGTH * sizeof( char ) );
    char *cmd2 = (char *) malloc( CMD2_LENGTH * sizeof( char ) );
    char *cmd3 = (char *) malloc( CMD3_LENGTH * sizeof( char ) );
    char *cmd4 =  (char *) malloc( CMD_LENGTH * sizeof( char ) );;


    printf("cmd> ");
    
    // while the user has input something
    while ( (input = readLine( stdin )) != NULL ) {
    
        // count the number of commands
        commands = sscanf( input, "%s %s %s %s", cmd1, cmd2, cmd3, cmd4 );
        printf("%s\n", input);
        
        // if the user input > 3 commands
        if ( commands > MAX_COMMAND_NUM )
            printf("Invalid command\n");
            
        // if the user input "list"
        else if ( strcmp( cmd1, "list" ) == 0 ) {
            
            switch ( commands ) {
                // if "list" is the only command
                case 1:
                    listEmployees( database, compareId, testAll, NULL);
                    break;
                // if there are 2 more commands after "list"
                case MAX_COMMAND_NUM:
                    // "list skill - "
                    if ( strcmp(cmd2, "skill") == 0 )
                        listEmployees( database, compareId, testSkill, cmd3);
                    // "list assignment - "
                    else if ( strcmp(cmd2, "assignment") == 0 )
                        listEmployees( database, compareSkill, testAssignment, cmd3);
                    else
                        printf("Invalid command\n");
                    break;
                default:
                    printf("Invalid command\n");
                    break;
            }   
                        
        }
        // if the user input "assign"
        else if ( strcmp( cmd1, "assign" ) == 0 && commands == MAX_COMMAND_NUM ) {
            if ( !assign( true, cmd2, cmd3, database ) )
                printf("Invalid command\n");
        }
        // if the user input "unassign"
        else if( strcmp( cmd1, "unassign" ) == 0 ) {
            if ( !assign( false, cmd2, "Available", database ) )
                printf("Invalid command\n");
        }
        // if the user input "quit"
        else if( strcmp( cmd1, "quit" ) == 0 ) {
            free( input );
            break;
        }
        else
            printf("Invalid command\n");
    
        free( input );
        printf("\ncmd> ");
    }
    
    // free the space for the commands
    free(cmd1);
    free(cmd2);
    free(cmd3); 
    free(cmd4);
    
    // free the database
    freeDatabase(database);
    
    // exit successfully
    return  EXIT_SUCCESS;
}