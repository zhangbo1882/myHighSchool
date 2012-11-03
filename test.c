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
int main()
{
	int i;
	dListLink *myList1 = dListLinkInit();
	dListLink *myList2 = dListLinkInit();
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
//	printf("destroy myList1\n");
	dListLinkDestroy(myList1);
//	printf("destroy myList2\n");
	dListLinkDestroy(myList2);
	return 0;
}
