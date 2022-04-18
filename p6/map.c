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
  	VType *value;
  
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
  	for ( int i = 0; i < len; i++ )
  		(m -> table)[ i ] = NULL;
  	
  	m -> size = 0;
  	m -> tlen = len;
  
  	return m;
}

int mapSize( Map *m )
{
  	return m -> size;
}

void mapSet( Map *m, VType *key, VType *val )
{
	unsigned int hash = key -> hash( key );
	int index = hash % (*m).tlen;
	
	Node *node = (Node *) malloc( sizeof( Node ));
	node -> key = key;
	node -> value = val;
	node -> next = NULL;
		
	if ( !( m -> table )[ index ])
		( m -> table)[ index ] = node; 
	else {
		Node *current = ( m -> table )[ index ];
		
		// if the current key matches the parameter key
		if ( current -> key -> equals( current -> key, key) ) {
			// free the parameter key because we're keeping the current key
			key -> destroy( key );
			// free the old value since we're overriding it
			current -> value -> destroy( current -> value );
			// free the node we made to insert
			free( node );
			// set the new value
			current -> value = val;
			return;
		}
		
		// traverse to first NULL node
		while ( current -> next ) {
			
			// if the current key matches
			if ( current -> key -> equals( current -> key, key) ) {
				// free the parameter key because we're keeping the current key
				key -> destroy( key );
				// free the old value since we're overriding it
				current -> value -> destroy( current -> value );
				// free the node we made to insert
				free( node );
				// set the new value
				current -> value = val;
				return;
			}
			current = current -> next;
		}

		// insert the node last in the list
		current -> next = node;
	}
	(*m).size ++;
}

VType *mapGet( Map *m, VType *key )
{
  	
  	unsigned int hash = key -> hash( key );
  	int index = hash % (*m).tlen;
  	
  	if ( !( m -> table )[ index ] )
  		return NULL;
  	else {
  		// start from first node in the index list
  		Node *current = ( m -> table )[ index ];
  		
  		// while the current node isn't null
  		while ( current ) {
  			// if the current key matches
  			if ( current -> key -> equals( current -> key, key ) )
  				return current -> value;
  			
  			// move to the next node if it's not null
  			if ( current -> next )
  				current = current -> next;
  			else
  				return NULL;
  		}
  	}
  	return NULL;
}

void freeNode( Node *node )
{
	// free the key and value
	node -> key -> destroy( node -> key );
	node -> value -> destroy( node -> value );
				
	// free the node
	free( node );
}

bool mapRemove( Map *m, VType *key )
{
	unsigned int hash = key -> hash( key );
	int index = hash % (*m).tlen;
	
	if ( !( m -> table)[ index ] )
		return false;
	else {
		Node *current = ( m -> table )[ index ];
		
		// special case for first node in the list
		if ( key -> equals( current -> key, key) ) {
		
			// store the node we're removing so we can free it
			Node *removed = current;
			
			// set first node in table to removed.next
			m -> table[ index ] = removed -> next;
			
			// free the node
			freeNode( removed );
			
			(*m).size --;
			return true;
		}
		
		while ( current -> next ) {
			
			// if the next Node has the key to remove
			if ( key -> equals(current -> next -> key, key) ) {
			
				// store the node we're removing so we can free it
				Node *removed = current -> next;
				
				// set current.next to removed.next
				current -> next = removed -> next;
				
				// free the node
				freeNode( removed );
				
				(*m).size --;
				return true;
			}
			
			current = current -> next;
		}
	}
	return false;
}

void freeMap( Map *m )
{
	// for each 'bucket' in the map table
  	for ( int i = 0; i < (*m).tlen; i++ ) {
  	
  		Node *removed = ( m -> table )[ i ];
  		if ( removed ) {
  			Node *current = removed -> next;
  			freeNode( removed );
  		
  			while ( current ) {
  				removed = current;
  				current = removed -> next;
  				freeNode( removed );
  			}
  		}
  	}
  	free( m -> table );
  	free( m );
}
