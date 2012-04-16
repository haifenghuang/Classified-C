
#include "CBang.h"
#include "CBString.h"

Class StringClass = NULL;

static void *initWithString(void *v, va_list *args);
static void *super(void *v);

static void *release(void *v, va_list *args);
static void *concatenate(void *v, va_list *args);
static void *length(void *v, va_list *args);
static void *print(void *v, va_list *args);

void string_class_init() {
	method m;

	StringClass = message(ClassClass, "init", "StringClass", ObjectClass, &super);

	m = mmethod(mstring("initWithString"), &initWithString);
	push_back(StringClass->methods, m);
	m = mmethod(mstring("release"), &release);
	push_back(StringClass->methods, m);
}

void *initWithString(void *v, va_list *args) {
	String s;
	method m;

	s = malloc(sizeof(struct _CBString));
	assert(s);
	
	s->class = StringClass;
	s->value = mstring(va_arg(*args, string));

	s->methods = create_list();
	m = mmethod(mstring("concatenate"), &concatenate);
	push_back(s->methods, m);
	m = mmethod(mstring("length"), &length);
	push_back(s->methods, m);
	m = mmethod(mstring("print"), &print);
	push_back(s->methods, m);

	message(ObjectClass, "initWithPointer", &(s->parent));

	return s;
}

void *super(void *v) {
	Integer i = (Integer)v;
	return &(i->parent);
}

void *release(void *v, va_list *args) {
	String s = (String)v;
	free(s->value);

	return s;
}

void *concatenate(void *v, va_list *args) {
	String s = (String)v;

	string part_one = s->value;
	string part_two = mstring(va_arg(*args, string));
	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);

	part_one = realloc(part_one, part_one_length + part_two_length + 1);
	assert(part_one);
 	
	strncat(part_one, part_two, part_two_length);

	s->value = part_one;

	return NULL;
}

void *length(void *v, va_list *args) {
	String s = (String)v;
	Integer length = message(IntegerClass, "initWithInt", strlen(s->value));
	return length;
}

void *print(void *v, va_list *args) {
	String s = (String)v;
	printf("%s", s->value);
	return NULL;
}
