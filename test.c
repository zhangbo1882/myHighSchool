#include "aaron.h"
char *name[5] = {"Eric", "Spiller", "Aaron", "Amos", "Terry"};
int digital[10] = {0,1,2,3,4,5,6,7,8,9};
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
	dListIter(myList1, dListLinkPrintString);
	dListIter(myList2, dListLinkPrintInt);

	/*Destory the link list*/
//	printf("destroy myList1\n");
	dListLinkDestroy(myList1);
//	printf("destroy myList2\n");
	dListLinkDestroy(myList2);
	return 0;
}
