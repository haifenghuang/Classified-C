
#include "../libcbang/CBang.h"
#include "MyClass.h"

int main(int argc, char **argv) {
	cbang_init();
	// myclass_init();

	Object o = message(ObjectClass, "init");
	message(o, "print");
	printf("\n");

	String st = message(StringClass, "initWithString", "test");
	message(st, "print");
	printf("\n");

	File f = message(FileClass, "initWithFilename", "Makefile");
	Scanner s = message(ScannerClass, "initWithFile", f);
	Integer i = message(IntegerClass, "initWithInt", 1);
	while (i->value != 0) {
		String token = message(s, "next");
		fprintf(stderr, "%s ", token->value);
		destruct(token);

		destruct(i);
		i = message(s, "has_next");
	}
	destruct(i);
	destruct(s);
	destruct(f);

	// CBNull n = construct("CBNull");
	// message(n, "print");
	// printf("\n");
	// destruct(n);

	// CBString s = construct("CBString", "OH HAI!");
	// message(s, "print");
	// printf("\n");
	// destruct(s);

	// MyClass mys = construct("MyClass", 77, "Foo");
	// message(mys, "concatenate", " Fighters");
	// message(mys, "print");
	// printf("\n");

	// CBInteger i = message(mys, "length");
	// printf("Length of string: %d\n", i->value);
	// destruct(i);
	// destruct(mys);

	// CBStack stack = construct("CBStack");
	// message(stack, "push", construct("CBString", "Ryan"));
	// message(stack, "push", construct("CBString", "Tanner"));
	// message(stack, "pop");
	// // message(stack, "pop");
	// s = message(stack, "peek");
	// if (s) {
	// 	printf("%s\n", s->value);
	// }
	// destruct(stack);

	printf("\n");
}
