
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

extern Class LinkedListClass;

typedef struct _LinkedList {
	struct _Object base;
	list *value;
} *LinkedList;

void LinkedListInit();

#endif
