
#ifndef CB_INTEGER_H
#define CB_INTEGER_H

#include "CBObject.h"

typedef struct _CBInteger {
	class type;
	int value;
	struct _CBObject parent;
} *CBInteger;

int cbinteger_to_int();

class cbinteger_init();

#endif