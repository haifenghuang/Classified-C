
#include "cbang.h"
#include "cbstring.h"

int main(int argc, char **argv) {
	cbang_init();

	var s = cbang_constructor("CBString", mstring("foo!"));
	
	printf("%s", cbstring_to_string(s));

	printf("\n");
}
