#ifndef __LIST__H__
#define __LIST__H__
#include "type.h"
typedef int (* removeFn)(void *data);
typedef int (* pCompareFn)(void *data1, void *data2);
typedef struct _listNode
{
	struct listNode* next;
	void *data;
}listNode;

typedef struct _list
{
	listNode *head;
	listNode *tail;
	pCompareFn compareFn;
	int size;
}List;

List *listInit();
int listInsertNext(List *list, listNode *p, const void *data);
int listInsertTail(List *list, const void *data);
int listInsertHead(List *list, const void *data);
int listDeleteNext(List *list, listNode *p, void **data);
int listSize(List *list);
int listDestory(List *list);
void listRemove(List *list, removeFn shouldRemove);
void listPrint(List *list);
int shouldRemove(void *data);
listNode *listFind(List *list,const void *data);
#endif
