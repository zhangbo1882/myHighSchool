#ifndef ___HASH___
#define __HASH__
#include "type.h"
typedef struct _hashTable hashTable;
typedef int (*pHashFunc)(hashTable *h, const void *key);
typedef int (*pCompareFunc)(const void *key1, const void *key2);
struct _hashTable
{
	int size;
	List **hash;
	pHashFunc hashFunc;
	pCompareFunc compareFunc;
};

void deleteHashTable(hashTable *htable);
hashTable* createHashTable(int size, pHashFunc hashFunc, pCompareFunc compareFunc);
int insertHashNode(hashTable *htable, const void *data);
int deleteHashNode(hashTable *htable, const void *data);
bool lookupHashTable(hashTable *htable, const void *key);



/*customized func*/
int myHashFunc(hashTable *h, const void *key);
int myCompareFunc(const void *key1, const void *key2);


#endif
	
