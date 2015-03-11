#include "aaron.h"
void *myMalloc(int size)
{
	void *p = malloc(size);
	if(!p)
	{
		printf("malloc size %d fail\n", size);
	}
	printf("malloc address %p\n", p);
	return p;	
}

void myFree(void **p)
{
	if(*p == NULL)
	{
		printf("free is NULL\n");
	}
	//myPrintf(("free memory %p\n", *p));
	free(*p);
	*p = NULL;
}
