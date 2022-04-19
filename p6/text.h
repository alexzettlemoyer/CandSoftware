/** 
    @file integer.h
    @author Alex Zettlemoyer
    Header for the Text subclass of VType
*/

#ifndef TEXT_H
#define TEXT_H

#include "vtype.h"

/** Subclass of VType for storing Strings. */
typedef struct {

    /** Inherited from VType */
    void (*print)( struct VTypeStruct const *v );

    /** Inherited from VType */
    bool (*equals)( struct VTypeStruct const *a, struct VTypeStruct const *b );

    /** Inherited from VType */
    unsigned int (*hash)( struct VTypeStruct const *b );

    /** Inherited from VType */
    void (*destroy)( struct VTypeStruct *v );

    /** String stored by this text */
    char *str;
  
    /** length of the string stored */
    int length;

} Text;

/** 
    Make an instance of Text holding a string parsed from the init string.
    @param init String containing the initializaiton string as text.
    @param n Optional return for the number of characters used from init.
    @return pointer to the new VType instance.
*/
VType *parseText( char const *init, int *n );

#endif
