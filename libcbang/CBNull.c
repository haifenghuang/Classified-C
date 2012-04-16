
#include "CBang.h"
#include "CBNull.h"

Class NullClass = NULL;

static void *init(void *v, va_list *args);

static void *release(void *v, va_list *args);

void null_class_init() {
	NullClass = message(ClassClass, "init", "Null", ObjectClass);

	push_back(NullClass->methods, mmethod("init", &init));
	
	push_back(NullClass->instance_methods, mmethod("release", &release));
}

void *init(void *v, va_list *args) {
	Null o;

	o = calloc(1, sizeof(struct _CBNull));
	assert(o);

	o->class = NullClass;
	o->methods = NullClass->instance_methods;
	o->parent = message(ObjectClass, "init");

	return o;
}

void *release(void *v, va_list *args) {
	Null o = (Null)v;
	message(o->parent, "release");
	free(o);
	return o;
}
