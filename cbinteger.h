
#ifndef CB_INTEGER_H
#define CB_INTEGER_H

typedef struct _cbinteger_data *cbinteger_data;

struct _cbinteger_data {
	int value;
};

int cbinteger_to_int();

class cbinteger_init();

#endif