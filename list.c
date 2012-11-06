#include "aaron.h"
List *listInit()
{
	List *p = (List *)myMalloc(sizeof(List));
	if(!p)
	{
		myPrintf(("Can not malloc memory\n"));
		return NULL;
	}
	p->head = NULL;
	p->tail = NULL;
	p->size = 0 ;
	return p;
}

int listInsertNext(List *list, listNode *p, const void *data)
{
	listNode *new = (listNode *)myMalloc(sizeof(listNode));
	if(!new)
	{
		myPrintf(("Can not malloc memory\n"));
		return -1;
	}
	new->data = data;
	if(!p)/*Insert into the head*/
	{
		if(!list->tail)
		{
			list->tail = new;
		}
		new->next = list->head;
		list->head = new;
	}
	else
	{
		new->next = p->next;
		p->next = new;
	
		if(p == list->tail)
		{
			list->tail = new;
		}
	}
	list->size++;
	return 0;
}

int listDeleteNext(List *list, listNode *p, void **data)
{
	listNode *del = NULL;
	if(!p) /*Delete the head*/
	{
		if(list->head == NULL)
		{
			myPrintf(("List is empty\n"));
			return -1;
		}
		*data = list->head->data;
		del = list->head;
		list->head = list->head->next;
		myFree(&del);
	}
	else
	{
		del = p->next;
		if(del == NULL)
		{
			myPrintf(("Deleted Node is NULL\n"));
			return -1;
		}
		p->next = del->next;
		myFree(&del);
		if(p->next == NULL)/*Delete the tail*/
		{
			list->tail = p;
		}
	}
	list->size--;
	return 0;
}

int listSize(List *list)
{
	return list->size;
}

int listDestory(List *list)
{
	void *data = NULL;
	listNode *p = list->head;
	while(list->head)
	{
		listDeleteNext(list, NULL, &data);
	}
	myFree(&list);
	return 0;
}
