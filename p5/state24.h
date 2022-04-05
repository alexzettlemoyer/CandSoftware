/**
 */

#ifndef _STATE64_H_
#define _STATE64_H_

#include <stdbool.h>

// Include filebuffer to get the byte type.
#include "filebuffer.h"

typedef struct {

	byte *data;
	int length;

} State24;

#endif
