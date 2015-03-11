#ifndef __LIST__H__
#define __LIST__H__
#include "type.h"
typedef struct _listNode
{
	struct listNode* next;
	void *data;
}listNode;

typedef struct _list
{
	listNode *head;
	listNode *tail;
	int size;
}List;

typedef int (* removeFn)(void *data);
List *listInit();
int listInsertNext(List *list, listNode *p, const void *data);
int listDeleteNext(List *list, listNode *p, void **data);
int listSize(List *list);
int listDestory(List *list);
void listRemove(List *list, removeFn shouldRemove);
void listPrint(List *list);
int shouldRemove(void *data);
#endif
