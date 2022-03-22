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

#define CMD_LENGTH 10
#define CMD2_LENGTH 12
#define CMD3_LENGTH 22

#define ASSIGNMENT_LENGTH 20
#define ID_LENGTH 4

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

int compareSkill( void const *va, void const *vb )
{
	struct Employee **a = ((struct Employee **) va);
	struct Employee **b = ((struct Employee **) vb);
	
	int compare = strcmp( (*a) -> skill, (*b) -> skill );
	
	if ( compare == 0 )
		compare = compareId( va, vb );
	
	return compare;
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
			
				if ( assign ==
				(strcmp((*database).employees[i] -> assignment, "Available") == 0) ) {
					
					strcpy((*database).employees[i] -> assignment, assignment);
					found = true;
				}			
			}
		}
	}	
	return found;
}

/**
	main method
*/
int main( int args, char *argv[] ) 
{
	// no files given on command line
	if ( args <= 1 ) {
		fprintf( stderr, "usage: agency <employee-file>*\n" );
		exit( EXIT_FAILURE );
	}
	
	struct Database *database = makeDataBase();
	//char const *str = "Available";

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
	
	while ( (input = readLine( stdin )) != NULL ) {
	
		commands = sscanf( input, "%s %s %s %s", cmd1, cmd2, cmd3, cmd4 );
		printf("%s\n", input);
		
		if ( commands > 3 )
			printf("Invalid command\n");
		else if ( strcmp( cmd1, "list" ) == 0 ) {
			
			switch ( commands ) {
				case 1:
					listEmployees( database, compareId, testAll, NULL);
					break;
				case 3:

					if ( strcmp(cmd2, "skill") == 0 )
						listEmployees( database, compareId, testSkill, cmd3);
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
		else if ( strcmp( cmd1, "assign" ) == 0 && commands == 3 ) {
			if ( !assign( true, cmd2, cmd3, database ) )
				printf("Invalid command\n");
		}
		else if( strcmp( cmd1, "unassign" ) == 0 ) {
			if ( !assign( false, cmd2, "Available", database ) )
				printf("Invalid command\n");
		}
		else if( strcmp( cmd1, "quit" ) == 0 ) {
			free( input );
			break;
		}
		else
			printf("Invalid command\n");
	
		free( input );
		printf("\ncmd> ");
	}
	free(cmd1);
	free(cmd2);
	free(cmd3);	
	free(cmd4);
	freeDatabase(database);
	
	return  0;
}