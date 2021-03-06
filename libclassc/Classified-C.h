
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <pthread.h>

#include "list.h"
#include "hashtable/hashtable.h"

#define CAT_CLASS(A) A ## Class
#define EXP_CLASS(A) CAT_CLASS(A)
#define CLASS_REF EXP_CLASS(CLASS)

#define NAME EXP_STR(CLASS)

#define CAT_STRUCT(A) struct _ ## A
#define EXP_STRUCT(A) CAT_STRUCT(A)
#define STRUCT EXP_STRUCT(CLASS)

#define CAT_INIT(A) A ## Init
#define EXP_INIT(A) CAT_INIT(A)
#define CLASS_INIT EXP_INIT(CLASS)

#ifndef SUPER_CLASS_REF
#define SUPER_CLASS_REF EXP_CLASS(SUPER)
#endif

#ifndef CLASSIFIEDC_H
#define CLASSIFIEDC_H

#define STR(A) #A

#define EXP_STR(A) STR(A)

#define proto(NAME) \
	static void *NAME(METHOD_ARGS)

#define METHOD_ARGS \
	void *v, va_list *args

#define defclass \
	Class CLASS_REF = NULL; \
	void CLASS_INIT() { \
		CLASS_REF = msg(ClassClass, "new", NAME, SUPER_CLASS_REF); \
		if (1)

#define defcon(METHOD) \
	void *METHOD(METHOD_ARGS) { \
		STRUCT *self = cc_alloc(sizeof(STRUCT)); \
		object_init(self); \
		((Object)self)->root = CLASS_REF; \
		if (1)

#define defstat(METHOD) \
	void *METHOD(METHOD_ARGS) { \
		Class self = CLASS_REF; \
		(void)self; \
		if (1)

#define def(METHOD) \
	void *METHOD(METHOD_ARGS) { \
		CLASS self = (CLASS)v; \
		(void)self; \
		if (1)

#define end }

#define instance(FUNCTION) \
	ht_insert_method(&CLASS_REF->instance_methods, #FUNCTION, strlen(#FUNCTION), mmethod(#FUNCTION, &FUNCTION), sizeof(struct _method));

#define static(FUNCTION) \
	ht_insert_method(&CLASS_REF->static_methods, #FUNCTION, strlen(#FUNCTION), mmethod(#FUNCTION, &FUNCTION), sizeof(struct _method));

#define constructor(FUNCTION) \
	static(FUNCTION)

#define nextArg(CLASS) va_arg(*args, CLASS)

#define msgSuper(...) msgCast(SUPER_CLASS_REF, self, __VA_ARGS__)

#define YES (void *)1
#define NO (void *)0

typedef char *cstring;
typedef void *(*fpointer) (void *v, va_list *args);
typedef struct _Object *Object;
typedef struct _Class *Class;
typedef size_t *boolean;

typedef struct _method {
	cstring name;
	fpointer function;
} method;

extern Object systemOut;

void cc_init();
void cc_end();
void *msg(const void *v, cstring message, ...);
void *msgCast(Class c, void *v, cstring message, ...);
void *msgWithMessage(void *arg);
void *cc_alloc(size_t size);
void call_method(void *v, va_list *args);
int test_by_calling_method(const void *v, va_list *args);
void msg_release(void *v);

method *mmethod(cstring name, fpointer function);
void dmethod(method *m);
cstring mstring(cstring s);

void ht_insert_method(hashtable **table, void *key, size_t key_size, void *value, size_t value_size);

int same_pointer(const void *a, const void *b);

#endif

#include "Object.h"
#include "Class.h"
#include "Null.h"
#include "Array.h"
#include "String.h"
#include "MutableString.h"
#include "Integer.h"
#include "Boolean.h"
#include "LinkedList.h"
#include "Stack.h"
#include "File.h"
#include "Scanner.h"
#include "Printer.h"
#include "Iterator.h"
#include "Thread.h"
#include "AutoReleasePool.h"

struct _message {
	Object target;
	cstring selector;
	LinkedList userData;
};
