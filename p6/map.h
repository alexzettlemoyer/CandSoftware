/** 
    @file map.h
    @author Alex Zettlemoyer
    Header for the map component, a hash map.
*/

#ifndef MAP_H
#define MAP_H

#include "vtype.h"
#include <stdbool.h>

/** Incomplete type for the Map representation. */
typedef struct MapStruct Map;

/** 
    Make an empty map.
    @param len Initial length of the hash table.
    @return pointer to a new map.
*/
Map *makeMap( int len );

/** 
    Get the size of the given map.
    @param m Pointer to the map.
    @return Number of key/value pairs in the map. 
*/
int mapSize( Map *m );
  
/** 
    Return the value associated with the given key. The returned VType
    is still owned by the map.
    @param m Map to query.
    @param k Key to look for in the map.
    @return Value associated with the given key, or NULL if the key
    isn't in the map.
*/
VType *mapGet( Map *m, VType *key );

/**
    Set a new Key/Value pair in the hash table
    If the key already exists in the map, its value is overwritten with the new val
    @param m Map to set key/value pair in
    @param key the Key to add
    @param val the Value to add
*/
void mapSet( Map *m, VType *key, VType *val );

/**
    Remove a Key/Value pair from the hash table
    @param m Map to remove key/value pair from
    @param key the Key to remove
    @return true if successfully removed, false otherwise
*/
bool mapRemove( Map *m, VType *key );

/** 
    Free all the memory used to store a map, including all the
    memory in its key/value pairs.
    @param m The map to free.
*/
void freeMap( Map *m );
  
#endif
