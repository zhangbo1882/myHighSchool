#include "common.h"
#include "aaron.h"
void deleteHashTable(hashTable *htable)
{
	int i = 0;
	for(i; i < htable->size; i++)
	{
		listDestory(htable->hash[i]);
	}
	free(htable); 
}
hashTable* createHashTable(int size, pHashFunc hashFunc, pCompareFunc compareFunc)
{
	hashTable *h = (hashTable *)malloc(sizeof(hashTable));
	int i = 0;
	if(!h)
	{
		printf("alloc fail\n");
		return NULL;
	}
	h->size = size;
	h->hash = malloc(sizeof(List ) * size);
	if(!h->hash)
	{
		printf("alloc fail\n");
		free(h);
		return NULL;
	}
	for(i; i < size; i++)
	{
		h->hash[i] = listInit(compareFunc);
		if(!h->hash[i])
		{
			printf("hash list init fail\n");
			return NULL;
		}
	}		
	h->hashFunc = hashFunc;
	h->compareFunc = compareFunc;
	return h;
}
int insertHashNode(hashTable *htable, const void *data)
{
	uint32 index = htable->hashFunc(htable, data);
	if(index >= htable->size)
	{
		printf("out of range\n");
		return -1;
	}
	List *hlist = htable->hash[index];
	listInsertTail(hlist,data);
	return 0;
}

bool lookupHashTable(hashTable *htable, const void *key)
{
	int index = htable->hashFunc(htable, key);
	if(index >= htable->size)
	{
		return false;
	}
	List *hlist = htable->hash[index];
	return (listFind(hlist, key) != NULL);
}

