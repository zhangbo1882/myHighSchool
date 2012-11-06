#ifndef __STACK__H__
#define __STACK__H__

typedef struct _listNode
{
	struct listNode *next;
	void* data;
}listNode;
typedef struct _stack
{
	listNode *head;
	int size;
}Stack;
Stack* stackInit();
int stackPop(Stack* stack, void **data);
int stackPush(Stack* stack, void* data);
void* stackPeek(Stack *stack);
int stackSize(Stack *stack);
int stackDestory(Stack* stack);
#endif
