#include "aaron.h"
void *myMalloc(int size)
{
	void *p = malloc(size);
	if(!p)
	{
		printf("malloc size %d fail\n", size);
	}
	return p;	
}

void myFree(void **p)
{
	if(*p == NULL)
	{
		printf("free is NULL\n");
	}
	printf("free memory %p\n", *p);
	free(*p);
	*p = NULL;
}
