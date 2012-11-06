#include "aaron.h"
Stack* stackInit()
{
	Stack *p = (Stack *)myMalloc(sizeof(Stack));
	if(!p)
	{
		myPrintf(("Can not malloc memory\n"));
		return NULL;
	}
	p->head = NULL;
	p->size = 0;
	return p;
}

int stackPush(Stack *stack, void *data)
{
	listNode *p = (listNode *)myMalloc(sizeof(listNode));
	if(!p)
	{
		myPrintf(("Can not malloc memory\n"));
		return -1;
	}
	p->data = data;
	if(stack->head)
	{
		p->next = stack->head;
	}
	stack->head  = p;
	stack->size++;
	return 0;
}

int stackPop(Stack *stack, void **data)
{
	if(stack->head)
	{
		*data = stack->head->data;
		stack->head = stack->head->next;
		stack->size--;
		return 0;
	}
	else
	{
		myPrintf(("Stack is empty\n"));
		return -1;
	}
}

void* stackPeek(Stack *stack)
{
	return stack->head;
}

int stackSize(Stack *stack)
{
	return stack->size;
}

int stackDestory(Stack *stack)
{
	listNode *p = stack->head;
	listNode *del = NULL;
	while(p)
	{
		del = p;
		p = p->next;
		myFree(del);
	}
	myFree(stack);
	return 0;
	
}

