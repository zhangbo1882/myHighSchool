#include "aaron.h"

Stack* stackInit()
{
	return listInit();
}

int stackPush(Stack *stack, const void *data)
{
	return listInsertNext(stack, NULL, data);
}

int stackPop(Stack *stack, void **data)
{
	return listDeleteNext(stack, NULL,data);
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
	return listDestory(stack);
}

