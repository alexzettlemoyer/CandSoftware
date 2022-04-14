/** 
    @file map.c
    @author
    Hash table implementation of a map.
*/

#include "map.h"
#include <stdlib.h>

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
  m->size = 0;

  // Complete the implementation.
  // ...
  
  return m;
}

int mapSize( Map *m )
{
  return m->size;
}

VType *mapGet( Map *m, VType *key )
{
  // Complete the implementation
  // ...

  return NULL;
}

void freeMap( Map *m )
{
  // Complete the implementation
  // ...
  
  free( m );
}
