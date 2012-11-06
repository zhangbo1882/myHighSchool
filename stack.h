#ifndef __STACK__H__
#define __STACK__H__
typedef List Stack;
int stackPop(Stack *stack, void **data);
int stackPush(Stack *stack, const void *data);
void  *stackPeek(Stack *stack);
int stackSize(Stack *stack);
int stackDestory(Stack *stack);
#endif
