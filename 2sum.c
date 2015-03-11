#include "common.h"
#include "type.h"
#include "aaron.h"
int myHashFunc(hashTable *h, const void *key)
{
	int index = *(int64 *)key % (h->size);
	return index > 0 ? index : -index;
}
int myCompareFunc(const void *data1, const void *data2)
{
	if(*(int64 *)data1 > *(int64 *)data2)
	   return 1;
	else if(*(int64 *)data1 < *(int64 *)data2)
		return -1;
	else 
		return 0;	
}
void hashInit(hashTable *htable, int64 a[], int len)
{
	int i = 0;
	int64 *pData = malloc(sizeof(int64) * len);
	if(!pData)
	{
		printf("alloc fail\n");
		return;
	}
	for(i; i < len; i++)
	{
		pData[i] = a[i];
		insertHashNode(htable, &pData[i]);
	}
	/*
	for(i = 0; i < HASH_SIZE; i++)
	{	
		if(htable->hash[i]->size > 1)
		{	
			printf("hashList[%d] Len: %d\n", i,htable->hash[i]->size);
		}
	}
	*/
}
bool twoSum(int64 a[], int len, int64 sum, hashTable *htable)
{
	int i = 0;
	int64 value;
	for(i; i < len; i++)
	{	
		value = sum - a[i];
		if((a[i] != value) && lookupHashTable(htable, &value))
		{
			//printf("%d + %d = %d\n", a[i], sum - a[i], sum);
			return true;
		}
	}
	return false;
	
}

int twoSumCount(int64 a[], int len, int64 begin, int64 end, hashTable *htable)
{
	int count = 0;
	int64 sum = begin;
	for(sum; sum <= end; sum++)
	{
		//printf("sum %lld\n", sum);
		if(twoSum(a, len, sum, htable))
		{
			count++;
		}
	}
	printf("count is %d\n", count);
	return count;
}
