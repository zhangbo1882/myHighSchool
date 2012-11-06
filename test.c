#include "aaron.h"
char *name[5] = {"Eric", "Spiller", "Aaron", "Amos", "Terry"};
int digital[10] = {0,1,2,3,4,5,6,7,8,9};
void findMax(void *ctx, dListLink *list, dListNode *p)
{
	int *max = (int *)ctx;
	if(*(int*)(p->data) > *max)
	{
		*max = *(int *)(p->data);
	}	
}
int dListMax(dListLink *list)
{
	int max =  0;
	dListIter(&max, list, findMax);
	return max;
}
void dListTest(void)
{
	int i;
	dListLink *myList1 = dListLinkInit();
	dListLink *myList2 = dListLinkInit();
	printf("==========================================\n");
	printf("Begin dList Test\n");
	if(myList1)
	{
		for(i = 0; i < 5; i++)
		{
			dListNode *p = dListNodeCreate(name[i]);
			dListLinkInsertTail(myList1, p);
		}
	}
	if(myList2)
	{
		for(i = 0; i < 10; i++)
		{
			dListNode *q = dListNodeCreate(&digital[i]);
			dListLinkInsertTail(myList2, q);
		}
	}
	/*Display the link*/
	printf("myList1 nodeCount: %d\n", myList1->nodeCount);
	printf("myList2 nodeCount: %d\n", myList2->nodeCount);
	dListIter(NULL, myList1, dListLinkPrintString);
	dListIter(NULL, myList2, dListLinkPrintInt);
	/*find the max value*/
	printf("max value of myList2 is %d\n", dListMax(myList2));
	/*Destory the link list*/
	printf("destroy myList1\n");
	dListLinkDestroy(myList1);
	printf("destroy myList2\n");
	dListLinkDestroy(myList2);
	printf("End dList Test\n");
	return;
}
void stackTest(void)
{
	int i = 0;
	void *data = NULL;
	printf("============================================\n");
	printf("Begin Stack Test\n");
	Stack *myStack = stackInit();
	if(myStack)
	{
		myPrintf(("push digital into stack\n"));
		for(i = 0; i < 10; i++)
		{
			stackPush(myStack, &digital[i]);
		}
#if 1
		myPrintf(("push name into stack\n"));
		for(i = 0; i < 5; i++)
		{
			stackPush(myStack, name[i]);
		}
		myPrintf(("pop the name\n"));
		for(i = 0; i < 5; i++)
		{
			stackPop(myStack, &data);
			printf("data: %s\n", (char *)(data));
		}
#endif		
		myPrintf(("Now stack size is %d\n", stackSize(myStack)));

		myPrintf(("pop the digital\n"));
		for(i = 0; i < 10; i++)
		{
			stackPop(myStack, &data);
			printf("data: %d\n", *(int *)data);
		}
		printf("Destory the Stack\n");
		printf("End Stack Test\n");
	}
	return;
}
int main()
{
	dListTest();
	stackTest();
	return 1;
}
