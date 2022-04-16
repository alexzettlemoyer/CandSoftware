/** 
    @file map.c
    @author
    Hash table implementation of a map.
*/

#include "map.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "vtype.h"

/** Node containing a key / value pair. */
typedef struct NodeStruct {
  	/** Pointer to the key part of the key / value pair. */
  	VType *key;
  
  	/** Pointer to the value part of the key / value pair. */
  	VType *val;
  
  	/** Pointer to the next node at the same element of this table. */
  	struct NodeStruct *next;
} Node;

/** Representation of a hash table implementation of a map. */
struct MapStruct {

  	/** Table of key / value pairs. */
  	Node **table;

  	/** Current length of the table. */
  	int tlen;
  
  	/** Current size of the map (number of different keys). */
  	int size;
};

Map *makeMap( int len )
{
  	Map *m = (Map *) malloc( sizeof( Map ) );
  	m -> size = 0;

  	m -> table = (Node **) malloc( len * sizeof( Node *));
  	m -> size = 0;
  	m -> tlen = len;
  
  	return m;
}

int mapSize( Map *m )
{
  	return m->size;
}

void mapSet( Map *m, VType *key, VType *val )
{
}

VType *mapGet( Map *m, VType *key )
{
  	
  	unsigned int hash = key -> hash( key );
  	int index = hash % (*m).tlen;
  	Node *current = NULL;
  	
  	if ( !( m -> table )[ index ] )
  		return NULL;
  	else {
  		current = ( m -> table )[ index ];
  		
  		while ( current ) {
  			if ( key -> equals( current -> key, key ) )
  				return current -> key;
  			
  			if ( current -> next )
  				current = current -> next;
  			else
  				return NULL;
  		}
  	}

  	return NULL;
}

bool mapRemove( Map *m, VType *key )
{
	return false;
}

void freeMap( Map *m )
{
  	// Complete the implementation
  	// ...
  
  	free( m );
}
