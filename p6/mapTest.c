// Simple test program for the text component.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vtype.h"
#include "map.h"
#include "integer.h"
#include "text.h"

int main()
{
  // Make a few values we use below.
  VType *v5 = parseInteger( "5", NULL );
  VType *v10 = parseInteger( "10", NULL );
  VType *v15 = parseInteger( "15", NULL );
  VType *v20 = parseInteger( "20", NULL );
  
  // Make a map with 3 slots in its hash table.
  Map *map = makeMap( 3 );
  assert( mapSize( map ) == 0 );

  // Put a the entry 5 -> 10 in the map.
  mapSet( map, parseInteger( "5", NULL ), parseInteger( "10", NULL ) );
  assert( mapSize( map ) == 1 );
  VType *v = mapGet( map, v5 );
  assert( v10->equals( v10, v ) );
  
  // Put a second entry, 10 -> 15 in the map.
  mapSet( map, parseInteger( "10", NULL ), parseInteger( "15", NULL ) );
  assert( mapSize( map ) == 2 );
  v = mapGet( map, v10 );
  assert( v15->equals( v15, v ) );

  // Check the key / value that was previously there.
  v = mapGet( map, v5 );
  assert( v10->equals( v10, v ) );

  // Change the value for key 5. to 5 -> 20
  mapSet( map, parseInteger( "5", NULL ), parseInteger( "20", NULL ) );
  assert( mapSize( map ) == 2 );
  v = mapGet( map, v5 );
  assert( v20->equals( v20, v ) );
  
  // Remove the value for key 10.
  assert( mapRemove( map, v10 ) );
  assert( mapSize( map ) == 1 );

  // Make sure that value is gone.
  v = mapGet( map, v10 );
  assert( v == NULL );
  
  // Try to remove a value that's not there.
  assert( mapRemove( map, v10 ) == false );
  assert( mapSize( map ) == 1 );
  
  // Free our maps.
  freeMap( map );

  // Free our temporary values.
  v5->destroy( v5 );
  v10->destroy( v10 );
  v15->destroy( v15 );
  v20->destroy( v20 );
  
  
  // TEST USING text
  // make some values
  VType *abc = parseText("\"abc\"", NULL);
  VType *alex = parseText("\"Alex\"", NULL);
  VType *csc = parseText("\"CSC230\"", NULL);
  VType *point = parseText("\"I love pointers \n <3\"", NULL);
  
  // and some integers to use
  v5 = parseInteger( "5", NULL );
  v10 = parseInteger( "10", NULL );
  v15 = parseInteger( "15", NULL );
  v20 = parseInteger( "20", NULL );
  
  // make a new map with 2 slots to create collisions
  Map *map2 = makeMap( 2 );
  assert( mapSize( map2 ) == 0 );
  
  // Put the entry "abc" -> 5 in the map
  mapSet( map2, parseText("\"abc\"", NULL), parseInteger( "5", NULL ) );
  assert( mapSize( map2 ) == 1 );
  v = mapGet( map2, abc );
  assert( v5 -> equals( v5, v ) );

  // Put another entry 20 -> "Alex" in the map
  mapSet( map2, parseInteger("20", NULL), parseText("\"Alex\"", NULL));
  assert( mapSize( map2 ) == 2);
  v = mapGet( map2, v20 );
  assert( alex -> equals( alex, v ));
  
  // SEG FAULT HERE
  // Put another entry "CSC230" -> "abc"
  mapSet( map2, parseText("\"CSC230\"", NULL), parseText("\"abc\"", NULL) );
  assert( mapSize( map2 ) == 3 );
  v = mapGet( map2, csc );

  assert( abc -> equals( abc, v ) );
  

  // Put another entry 10 -> "I love pointers \n <3"
  mapSet( map2, parseInteger( "10", NULL ), parseText("\"I love pointers \n <3\"", NULL));
  assert( mapSize( map2 ) == 4 );
  v = mapGet( map2, v10 );
  assert( point -> equals( point, v ) );

  // Change the value of "abc" -> to 15
  mapSet( map2, parseText("\"abc\"", NULL), parseInteger( "15", NULL ) );
  assert( mapSize( map2 ) == 4 );
  v = mapGet( map2, abc );
  assert( v15 -> equals( v15, v ) );
   
  // free the map
  freeMap( map2 );
   
  // free temporary variables
  abc -> destroy( abc );
  alex -> destroy( alex );
  csc -> destroy( csc );
  point -> destroy( point );
  
  v5->destroy( v5 );
  v10->destroy( v10 );
  v15->destroy( v15 );
  v20->destroy( v20 );
  
  return EXIT_SUCCESS;
}
