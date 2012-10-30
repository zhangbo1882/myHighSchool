#include "aaron.h"
dListLink *dListLinkInit()
{
	dListLink *list = (dListLink *)myMalloc(sizeof(dListLink));
	if(list)
	{
		list->head = NULL;
		list->tail = NULL;
		list->nodeCount = 0;
	}
	return list;
}

dListNode *dListNodeCreate(void *data)
{
	dListNode *p = (dListNode *)myMalloc(sizeof(dListNode));
	if(p)
	{
		p->prev = NULL;
		p->next = NULL;
		p->data = data;
	}
	return p;
}

int dListNodeFree(dListNode *p)
{
	myFree(&p);
	return 1;
}
 
int dListLinkInsertHead(dListLink *list, dListNode *p)
{
	if(!list || !p)
	{
		printf("%s %d list or node is NULL\n", __FUNCTION__, __LINE__);
		return -1;
	}
	if(list->head == NULL)
	{
		list->head = p;
		list->tail = p;
		p->prev = NULL;
		p->next = NULL;

	}
	else
	{
		p->prev = NULL;
		p->next = list->head;
		list->head->prev = p;
		list->head = p;
	}

	list->nodeCount++;
	return 0;
}

int dListLinkInsertTail(dListLink *list, dListNode *p)
{
	if(!list || !p)
	{
		printf("%s %d list or node is NULL\n", __FUNCTION__, __LINE__);
		return -1;
	}
	if(list->tail == NULL)
	{
		list->head = p;
		list->tail = p;
		p->prev = NULL;
		p->next = NULL;
	}
	else
	{
		p->prev = list->tail;
		list->tail->next = p;
		list->tail = p;
		p->next = NULL;
	}
	list->nodeCount++;
	return 0;
}

int dListLinkInsertB(dListLink *list, dListNode *pos, dListNode *p)
{
	if(list->tail == pos)
	{
		dListLinkInsertTail(list, p);
		return 0;
	}
	else
	{
		p->next = pos->next;
		p->next->prev = p;
		pos->next = p;
		p->prev = pos;
	}
	return 0;
}

int dListLinkInsertF(dListLink *list, dListNode *pos, dListNode *p)
{
	if(list->head == pos)
	{
		dListLinkInsertHead(list, p);
		return 0;
	}
	else
	{
		pos->prev->next = p;
		p->prev = pos->prev;
		p->next = pos;
		pos->prev = p;
	}
	return 0;
}
int dListLinkDeleteHead(dListLink *list)
{
	dListNode *p = list->head;
	if(!p)
	{
		return -1;
	}
	if(list->head != list->tail)
	{
		list->head = list->head->next;
		list->head->prev = NULL;
	}
	else
	{
		list->head = NULL;
		list->tail = NULL;
	}
	list->nodeCount--;
	dListNodeFree(p);
	return 0;
}

int dListLinkDeleteTail(dListLink *list)
{
	dListNode *p = list->tail;
	if(!p)
	{
		return -1;
	}
	if(list->head != list->tail)
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	else
	{
		list->head = NULL;
		list->tail = NULL;
	}
	dListNodeFree(p);
	list->nodeCount--;
	return 0;
}

int dListLinkDelete(dListLink *list, dListNode *p)
{
	if(list->head == p)
	{
		dListLinkDeleteHead(list);
		return 0;
	}
	else if(list->tail == p)
	{
		dListLinkDeleteTail(list);
		return 0;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		dListNodeFree(p);
		list->nodeCount--;
	}

	return 0;
}

int dListLinkDestroy(dListLink *list)
{
	dListNode *curr = list->head;
	dListNode *del = curr;
	while(curr)
	{
		del = curr;
		curr = curr->next;
		dListLinkDelete(list, del);
	}
	myFree(&list);
	return 0;
}

int dListIter(dListLink *list, dListIterCB fn)
{
	dListNode *p = list->head;
	while(p)
	{
		fn(list, p);
		p = p->next;
	}
	return 0;
}

void dListLinkPrintInt(dListLink *list,dListNode *p)
{
	printf("data: %d\n",*(int *)(p->data));
}
void dListLinkPrintString(dListLink *list,dListNode *p)
{
	printf("data: %s\n",(char *)(p->data));
}
void dListLinkPrintData(dListLink *list,dListNode *p)
{
	printf("data: %p\n",(p->data));
}
