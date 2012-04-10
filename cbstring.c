
#include "CBang.h"
#include "CBString.h"

static class this = NULL;

static var constructor();
static void destructor(var v);
static var concatenate();
static var length();
static var print();

string cbstring_to_string(var v) {
	return ((cbstring_data)v->data)->value;
}

class cbstring_init() {
	method m;

	if (this) {
		return this;
	}

	this = mclass(mstring("CBString"), NULL, &constructor, &destructor);

	m = mmethod(mstring("concatenate"), &concatenate);
	push_back(this->methods, m);
	m = mmethod(mstring("length"), &length);
	push_back(this->methods, m);
	m = mmethod(mstring("print"), &print);
	push_back(this->methods, m);

	return this;
}

var constructor(va_list args) {
	var v = mvar(this);

	v->data = malloc(sizeof(struct _cbstring_data));
	((cbstring_data)v->data)->value = va_arg(args, string);

	return v;
}

void destructor(var v) {
	free(((cbstring_data)v->data)->value);
}

var concatenate(var v, va_list args) {
	string part_one = ((cbstring_data)v->data)->value;
	string part_two = va_arg(args, string);
	int part_one_length = strlen(part_one);
	int part_two_length = strlen(part_two);

	realloc(part_one, sizeof(char) * (part_one_length + part_two_length + 1));

	memcpy(&part_one[part_one_length], part_two, sizeof(char) * (part_two_length + 1));

	free(part_two);

	return NULL;
}

var length(var v, va_list args) {
	var length = construct("CBInteger", strlen(cbstring_to_string(v)));
	return length;
}

var print(var v, va_list args) {
	printf("%s", cbstring_to_string(v));
	return NULL;
}