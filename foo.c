
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cbang.h"

char *strendtrim(char *s);

int main(int argc, char **argv) {
	var temp;
	_cbang_init();

	var a_null = cbang_constructor("Null");
	temp = cbang_message_send(a_null, "describe");

	printf("\n");
}
