
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cbang.h"

char *strendtrim(char *s);

int main(int argc, char **argv) {
	var temp;
	_objc_init();

	var a_null = objc_constructor("Null");
	temp = objc_message_send(a_null, "describe");

	printf("\n");
}
