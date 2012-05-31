
#include "Classified-C.h"

IMPLEMENTATION(IntegerClass);

PROTOTYPE(newWithInt);
PROTOTYPE(initWithInt);
PROTOTYPE(dealloc);
PROTOTYPE(equals);
PROTOTYPE(description);

void integer_class_init() {
	IntegerClass = msg(ClassClass, "new", "Integer", ObjectClass);

	REGISTER_CLASS_METHOD(IntegerClass, "newWithInt", newWithInt);
	
	REGISTER_METHOD(IntegerClass, "initWithInt", initWithInt);
	REGISTER_METHOD(IntegerClass, "dealloc", dealloc);
	REGISTER_METHOD(IntegerClass, "equals", equals);
	REGISTER_METHOD(IntegerClass, "description", description);
}

DEFINE(newWithInt) {
	NEW(IntegerClass, struct _Integer);

	initWithInt(self, args);

	return self;
}

DEFINE(initWithInt) {
	CONTEXT(Integer);

	self->value = NEXT_ARG(size_t);

	return self;
}

DEFINE(dealloc) {
	CONTEXT(Integer);

	return msg_cast(ObjectClass, self, "dealloc");
}

DEFINE(equals) {
	CONTEXT(Integer);

	size_t other = NEXT_ARG(size_t);

	if (self->value == other) {
		return YES;
	}

	return NO;
}

DEFINE(description) {
	CONTEXT(Integer);

	return msg(StringClass, "newWithFormatCString", "%d", self->value);
}