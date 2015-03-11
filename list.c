#include "aaron.h"
List *listInit(pCompareFn compareFn)
{
	List *p = (List *)malloc(sizeof(List));
	if(!p)
	{
		myPrintf(("Can not malloc memory\n"));
		return NULL;
	}
	p->head = NULL;
	p->tail = NULL;
	p->size = 0 ;
	p->compareFn = compareFn;
	return p;
}
void listPrint(List *list)
{
	int i = 0;
	listNode *cur = list->head;
	while(cur)
	{
		printf("Node[%d]: %d \n",i+1, *(int *)(cur->data));
		cur = cur->next;
		i++;
	}
	return;
}
int listInsertNext(List *list, listNode *p, const void *data)
{
	listNode *new = (listNode *)malloc(sizeof(listNode));
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

int listInsertTail(List *list, const void *data)
{
	listInsertNext(list, list->tail, data);
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

int shouldRemove(void *data)/*If the data is odd return true*/
{
	if((*(int *)data)%2 == 1)
		return true;
	else
		return false;
}
void listRemove(List *list, removeFn shouldRemove)
{
	listNode *remove = NULL;
	listNode **cur = &(list->head);
	printf("%s, %d cur: %p, *cur: %p\n", __FUNCTION__, __LINE__, cur, *cur);
	while(*cur)
	{
		remove = *cur;
		printf("%s, %d remove: %p,\n", __FUNCTION__, __LINE__, remove);
		if(shouldRemove(remove->data))
		{
			*cur = remove->next;
			printf("%s, %d *cur: %p,\n", __FUNCTION__, __LINE__, *cur);
			myFree(&remove);
		}
		else
		{
			cur = &(remove->next);
			printf("%s, %d cur: %p, *cur: %p\n", __FUNCTION__, __LINE__, cur, *cur);

		}
	}
	
}

listNode* listFind(List *list, const  void *data)
{
	if(!list)
	{
		return false;

	}
	listNode *p = list->head;
	while(p)
	{
		if(list->compareFn(data, p->data) == 0)
			return p;
		else
			p = p->next;
	}
	return NULL;
}
